#include <iostream>
#include<vector>
#include<string>
#include <stack>

using namespace std;

template<typename tkey>
class comparer
{
public:
	virtual int compare(const tkey& left, const tkey& right) const = 0;
	virtual ~comparer() = default;
};



class Int_comparer : public comparer<int>
{
public:
	Int_comparer() {}
	int compare(const int& left, const int& right) const
	{
		if (left > right)
			return 1;
		else
		{
			if (left == right)
				return 0;
			else
				return -1;
		}
	}
};



template<typename tkey, typename tvalue>
class assoc_container
{
public:
	virtual void insert(const tkey& key, const tvalue& value) = 0;
	virtual tvalue remove(const tkey& key) = 0;
	virtual tvalue find(const tkey& key) = 0;
	virtual ~assoc_container() = default;
};



template<typename tkey, typename tvalue>
class binary_search_tree : public assoc_container<tkey, tvalue>
{
protected:
	class node
	{
	public:
		node(const tkey& key, const  tvalue& value)
		{
			this->key = key;
			this->value = value;
			this->left = nullptr;
			this->right = nullptr;
		}

		node(node& tree)
		{
			this->key = tree.key;
			this->value = tree.value;
		}

		tkey key;
		tvalue value;
		node* left;
		node* right;
	};
private:
	node* root;

public:
	binary_search_tree(comparer<tkey>* _cmp)
	{
		this->root = nullptr;
		this->cmp = _cmp;
		inserter = new inserting_template();
		remover = new removing_template();
		finder = new finding_template();
	}
	binary_search_tree(const binary_search_tree<tkey, tvalue>& tree)
	{
		this->cmp = tree.cmp;
		if (tree.root != nullptr)
		{
			this->root = new node(*tree.root);
			copy(root->left, tree.root->left);
			copy(root->right, tree.root->right);
		}
	}

protected:
	class inserting_template
	{
	public:
		virtual void add(node*& _node, comparer<tkey>* cmp, const tkey& key, const tvalue& value)
		{
			if (_node == nullptr)
			{
				node* new_node = new node(key, value);
				_node = new_node;
			}
			else
			{
				int way = 2;
				node* new_node = new node(key, value);
				node* tmp = _node;

				do
				{
					way = cmp->compare(key, tmp->key);
					if (way == -1)
					{
						if (tmp->left == nullptr)
							tmp->left = new_node;
						else
							tmp = tmp->left;
					}
					else
					{
						if (way == 1)
						{
							if (tmp->right == nullptr)
								tmp->right = new_node;
							else
								tmp = tmp->right;
						}
					}
				} while ((tmp->right != nullptr) && (tmp->left != nullptr));

				way = cmp->compare(key, tmp->key);
				if (way == -1)
				{
					if (tmp->left == nullptr)
						tmp->left = new_node;
					else
						tmp = tmp->left;
				}
				else
				{
					if (way == 1)
					{
						if (tmp->right == nullptr)
							tmp->right = new_node;
						else
							tmp = tmp->right;
					}
				}

			}
		}
	};

	class removing_template
	{
	public:
		tvalue remove(node*& _node, comparer<tkey>* cmp, const tkey& key)
		{
			int way = 2;

			node* s_node = _node;
			node* parent = nullptr;

			if (s_node != nullptr)
			{
				while (way != 0)
				{
					way = cmp->compare(key, s_node->key);

					if (way == 1)
					{
						parent = s_node;
						s_node = s_node->right;
					}
					else
						if (way == -1)
						{
							parent = s_node;
							s_node = s_node->left;
						}
				}
			}
			else
				throw binary_search_tree<tkey, tvalue>::find_error();

			if (s_node->key != key)
				throw binary_search_tree<tkey, tvalue>::find_error();

			if ((s_node->left == nullptr) && (s_node->right == nullptr))
			{
				if (parent->left == s_node)
					parent->left = nullptr;
				else
					if (parent->right == s_node)
						parent->right = nullptr;
				tvalue val = s_node->value;
				delete s_node;
				return val;
			}
			else
			{
				if ((s_node->left == nullptr) && (s_node->right != nullptr))
				{
					if (parent->left == s_node)
						parent->left = s_node->right;
					else
						if (parent->right == s_node)
							parent->right = s_node->right;
					tvalue val = s_node->value;
					delete s_node;
					return val;
				}
				else
				{
					if ((s_node->left != nullptr) && (s_node->right == nullptr))
					{
						if (parent->left == s_node)
							parent->left = s_node->left;
						else
							if (parent->right == s_node)
								parent->right = s_node->left;
						tvalue val = s_node->value;
						delete s_node;
						return val;
					}
					else
					{
						node* parent_tmp = s_node;
						node* tmp = s_node->right;

						while (tmp->left != nullptr)
						{
							parent_tmp = tmp;
							tmp = tmp->left;
						}

						if (parent != nullptr)
						{
							if (parent->left == s_node)
								parent->left = tmp;
							else
								if (parent->right == s_node)
									parent->right = tmp;
						}

						if (s_node != parent_tmp)
						{
							parent_tmp->left = tmp->right;
							tmp->right = s_node->right;
						}
						tmp->left = s_node->left;

						tvalue val = s_node->value;
						delete s_node;
						return val;
					}
				}
			}

		}
	};


	class finding_template
	{
	public:
		tvalue find(node*& _node, comparer<tkey>* cmp, const tkey& key)
		{
			if (_node != nullptr)
			{
				int way = cmp->compare(key, _node->key);
				if (way == 0)
					return _node->value;
				else
					if (way == 1)
						find(_node->right, cmp, key);
					else
						if (way == -1)
							find(_node->left, cmp, key);
						else
							throw binary_search_tree<tkey, tvalue>::find_error();
			}
		}
	};

	int clean(node* _node)
	{

		if (_node->left != nullptr)
			clean(_node->left);
		if (_node->right != nullptr)
			clean(_node->right);
		delete _node;

		return 0;

	}


private:
	inserting_template* inserter;
	removing_template* remover;
	finding_template* finder;

	comparer<tkey>* cmp;

public:
	virtual ~binary_search_tree()
	{
		delete inserter;
		delete remover;
		delete finder;

		if (root != nullptr)
			clean(root);
	}

	void insert(const tkey& key, const tvalue& value) override
	{
		inserter->add(root, cmp, key, value);
	}

	tvalue remove(const tkey& key) override
	{
		return remover->remove(root, cmp, key);
	}

	tvalue find(const tkey& key) override
	{
		return finder->find(root, cmp, key);
	}

	virtual binary_search_tree& operator=(const binary_search_tree<tkey, tvalue>& tree)
	{
		if (root != nullptr)
			clean(root);
		root = copy(this->root, tree.root);
		return *this;
	}

	void start_pre_order_traversal(void(*funck)(const tkey& key, const tvalue& value, int depth))
	{
		int depth = 0;
		if (root != nullptr)
			pre_order_traversal(funck, root, depth);
	}

	void pre_order_traversal(void(*funck)(const tkey& key, const tvalue& value, int depth), node*& root, int depth)
	{
		if (root != nullptr)
		{
			(*funck)(root->key, root->value, depth);
			depth++;
			pre_order_traversal(funck, root->left, depth);
			pre_order_traversal(funck, root->right, depth);
			depth--;
		}
	}

	void start_in_order_traversal(void(*funck)(const tkey& key, const tvalue& value, int depth))
	{
		int depth = 0;
		if (root != nullptr)
			in_order_traversal(funck, root, depth);
	}

	void in_order_traversal(void(*funck)(const tkey& key, const tvalue& value, int depth), node*& root, int depth)
	{
		if (root)
		{
			depth++;
			in_order_traversal(funck, root->left, depth);
			depth--;
			(*funck)(root->key, root->value, depth);
			depth++;
			in_order_traversal(funck, root->right, depth);
			depth--;
		}
	}

	void start_post_order_traversal(void(*funck)(const tkey& key, const tvalue& value, int depth))
	{
		int depth = 0;
		if (root != nullptr)
			post_order_traversal(funck, root, depth);
	}

	void post_order_traversal(void(*funck)(const tkey& key, const tvalue& value, int depth), node*& root, int depth)
	{
		if (root)
		{
			depth++;
			post_order_traversal(funck, root->left, depth);
			post_order_traversal(funck, root->right, depth);
			depth--;
			(*funck)(root->key, root->value, depth);
		}
	}

protected:

	virtual node* copy(node* old_node, node* new_node)
	{
		if (old_node == nullptr)
			return new_node;
		new_node = new node(old_node->key, old_node->value);
		new_node->left = copy(old_node->left, new_node->left);
		new_node->right = copy(old_node->right, new_node->right);
		return new_node;
	}


public:
	class tree_exception : public std::exception
	{
	public:
		tree_exception(const string& descr)
		{
			description = descr;
		}
		tree_exception() {}
		const char* what() const noexcept
		{
			return description.c_str();
		}

	protected:
		string description;
	};

	class insert_error : public tree_exception
	{
	public:
		insert_error()
		{
			tree_exception::description = "Insert error: the element with this key doesn't exist";
		}
	};

	class append_error : public tree_exception
	{
	public:
		append_error()
		{
			tree_exception::description = "Append error: the element with this key already exist";
		}
	};

	class errase_error : public tree_exception
	{
	public:
		errase_error()
		{
			tree_exception::description = "Errase error: the element with this key doesn't exist";
		}
	};

	class find_error : public tree_exception
	{
	public:
		find_error()
		{
			tree_exception::description = "Get value error: the element with this key doesn't exist";
		}
	};

};

template <typename tkey, typename tvalue>
void print_node(tkey key, tvalue data, int depth)
{
	std::cout << "Node " << key << ": data - " << data << "; dempth - " << depth << std::endl;
}

template <typename tkey, typename tvalue>
void print_all_order(binary_search_tree<tkey, tvalue>& tree)
{
	cout << endl << "Preorder:" << endl;
	tree.start_pre_order_traversal(print_node);

	cout << endl << "Inorder:" << endl;
	tree.start_in_order_traversal(print_node);

	cout << endl << "Postorder:" << endl;
	tree.start_post_order_traversal(print_node);
}

int main()
{
	cout << "Lab 2 Number 1 of Nosov Alexander M8O-211B-20" << endl;
	int a = 10;
	binary_search_tree<int, int> tree(new Int_comparer);

	try
	{
		tree.insert(8, 1);
		tree.insert(5, 2);
		tree.insert(4, 3);
		tree.insert(14, 4);
		tree.insert(10, 5);
		tree.insert(19, 6);
		tree.insert(7, 7);
		tree.insert(2, 8);

		print_all_order(tree);

		cout << tree.find(19);

		tree.remove(14);

		print_all_order(tree);
	}
	catch (binary_search_tree<int, int>::tree_exception& ex)
	{
		cout << "Error: " << ex.what() << std::endl;
	}

	return 0;
}