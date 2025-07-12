#ifndef BST_H
#define BST_H

template <typename T>
class BST
{
private:
    struct Node
    {
        T data;
        Node *left;
        Node *right;

        Node(const T &data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node *root;

    void insert(Node *&node, const T &data)
    {
        if (!node)
        {
            node = new Node(data); 
        }
        else if (data < node->data)
        {
            insert(node->left, data);
        }
        else if (node->data < data)
        {
            insert(node->right, data);
        }
    }

    template <typename Func>
    void inOrderTraversal(Node *node, Func visit) const
    {
        if (node)
        {
            inOrderTraversal(node->left, visit);
            visit(node->data);
            inOrderTraversal(node->right, visit);
        }
    }

    const T *Search(Node *node, int id) const
    {
        if (!node)
            return nullptr;
        else if (id == node->data.getId())
            return &(node->data);
        else if (id < node->data.getId())
            return Search(node->left, id);
        else
            return Search(node->right, id);
    }

    T *searchMutable(Node *node, int id)
    {
        if (!node)
            return nullptr;

        if (node->data.getId() == id)
            return &(node->data);
        else if (id < node->data.getId())
            return searchMutable(node->left, id);
        else
            return searchMutable(node->right, id);
    }

public:
    BST() : root(nullptr) {}

    void insert(const T &data)
    {
        insert(root, data);
    }

    template <typename Func>
    void inOrder(Func visit) const
    {
        inOrderTraversal(root, visit);
    }

    const T *Searchbyid(int id) const
    {
        return Search(root, id);
    }

    T *SearchBymutable(int id)
    {
        return searchMutable(root, id);
    }
};

#endif // BST_H
