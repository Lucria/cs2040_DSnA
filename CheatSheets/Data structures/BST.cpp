class BST {
    // Precond: this BST does not store duplicates
    // -1 is used to signify a non-existent value return
    
private:
    struct vertex {
        vertex * parent;
        vertex * left;
        vertex * right;
        int key;
    };
    
    vertex * root;
    int size;
    vertex * search_recur(int key, vertex * curr) {
        if (curr == NULL) return curr;
        
        else if (curr->key == key) return curr;

        else if (curr->key < key) return search_recur(key, curr->right);
        else return search_recur(key, curr->left);
    }

    int findMax_recur (vertex * curr) {
        if (curr == NULL) return -1; // Empty
        if (curr->right != NULL) return findMax_recur(curr->right); // go right
        else return curr->key;
    }
    
    int findMin_recur (vertex * curr) {
        if (curr == NULL) return -1; // Empty
        if (curr->left != NULL) return findMin_recur(curr->left); // go left
        else return curr->key;
    }
    
    
    void inorder_recur (vertex * curr) {
        if (curr == NULL) return;
        inorder_recur(curr->left);
        cout << curr->key << " ";
        inorder_recur(curr->right);
    }
    
    // Will eventually return root at the end of the recursive stack
    vertex * insert_recur (vertex * curr, int key) {
        if (curr == NULL) {
            // insertion point is found
            curr = new vertex;
            curr->key = key;
            curr->parent = curr->left = curr->right = NULL;
            size++;
        }
        
        else if (curr->key < key) {
            // search to the right
            curr->right = insert_recur(curr->right, key);
            curr->right->parent = curr; // slowly bubbling up curr to be root
        }
        else {
            // search to the left
            curr->left = insert_recur(curr->left, key);
            curr->left->parent = curr;
        }
        return curr;
    }
    
    // Will eventually return root at the end of the recursive stack
    vertex * remove_recur (vertex * curr, int key) {
        if (curr == NULL)  return curr; // cannot find the item to be deleted
        if (curr->key == key) {
            // 3 cases
            if (curr->right == NULL && curr->left == NULL) {
                // Leaf
                delete curr;
            }
            else if ((curr->left != NULL && curr->right == NULL) || (curr->left == NULL && curr->right != NULL)) {
                // Only one child
                vertex * temp = curr;
                if (curr->left != NULL) {
                    // Left contains a child
                    curr->left->parent = curr->parent;
                    curr = curr->left;
                    delete temp;
                }else {
                    // Right contains a child
                    curr->right->parent = curr->parent;
                    curr = curr->right;
                    delete temp;
                }
            }
            else {
                // Find successor or predecessor also can
                int successorV = successor(key);
                curr->key = successorV; // Let current vertex key be the successor
                curr->right = remove_recur(curr->right, successorV);
            }

        }
        // Find left and right if current vertex key is not the one we want. - search
        else if (curr->key < key) curr->right = remove_recur(curr->right, key);
        else curr->left = remove_recur(curr->left, key);
        
        return curr;
    }
    
public:
    
    BST () {
        // constructor
        size = 0;
        root = NULL;
    }
    
    bool search (int key) {
        if (search_recur(key, root) != NULL) return true;
        return false;
    }
    
    // Find Min/ Max will take O(h), h = height of tree. h can be as big as N if all vertices are connected to the right
    
    int findMax () {
        return findMax_recur(root);
    }
    
    int findMin () {
        return findMin_recur(root);
    }
    
    // Predecessor and successor will also run in O(h)
    
    int successor (int key) {
        vertex * curr = search_recur(key, root);
        if (curr == NULL) return -1;
        if (curr->right != NULL) return findMin_recur(curr->right);
        
        else {
            vertex * p = curr->parent, * T = curr;
            
            while (p != NULL && T == p->right) {
                T = p;
                p = T->parent;
            }
            if (p == NULL) return -1;
                else return p->key;
        }
        return -1;
    }
    
    int predecessor (int key) {
        vertex * curr = search_recur(key, root);
        if (curr == NULL) return -1;
        if (curr->left != NULL) return findMax_recur(curr->left);
        else {
            vertex * p = curr->parent, * T = curr;
            
            while (p != NULL && T == p->left) {
                T = p;
                p = T->parent;
            }
            if (p == NULL) return -1;
            else return p->key;
        }
        return -1;
    }
    
    // Commonly used for DFS
    // inorder traversal will give a sorted sequence O(n)
    void inorder () {
        inorder_recur(root);
        cout << endl;
    }
    
    // O(h) as we have to search first then insert if not found
    
    void insert (int key) {
        root = insert_recur(root, key);
    }
    
    /*
     Removal:
     - O(h) as we depend on search too
     Cases:
     - Vertex is a leaf = just search and remove by deleting
     - Vertex is internal + only 1 child = We just connect this vertex's parent with its only child
     - Vertex is internal + 2 children = We set itself to same value as its successor (successor means we have to keep travelling down the right subtree then leftwards),
     then delete duplicate in right subtree (whilst moving its child along to the current vertex too)
    */
    
    void remove (int key) {
        root = remove_recur(root, key);
    }
};