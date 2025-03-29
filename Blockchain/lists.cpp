using namespace data;

class list {
    class circular_linked_list {
    protected:
        node* root;

    public:
        // Constructor: Initialize the list as circular if a starting node is provided
        circular_linked_list(node* starting_node) {
            if (starting_node != nullptr) {
                starting_node->next = starting_node;
                starting_node->previous = starting_node;
            }
            root = starting_node;
        }

        // Insert a new node after the specified previous_node
        node* insert_after(node* previous_node, char* contents_to_insert) {
            if (previous_node == nullptr) {
                return nullptr; // Cannot insert after a null node
            }
            node* new_node = new node();
            new_node->contents = contents_to_insert;
            new_node->next = previous_node->next;
            new_node->previous = previous_node;
            previous_node->next = new_node;
            new_node->next->previous = new_node;
            return new_node;
        }

        // Find a node in the list, return nullptr if not found
        node* find_node(node* node_to_find) {
            if (root == nullptr) return nullptr;
            node* current = root;
            do {
                if (current == node_to_find) return current;
                current = current->next;
            } while (current != root);
            return nullptr; // Node not found after full traversal
        }

        // Delete a specified node from the list
        bool delete_node(node* node_to_delete) {
            if (root == nullptr) return false;

            node* current = find_node(node_to_delete);
            if (current == nullptr) return false;

            // Case 1: Only one node in the list
            if (current->next == current) {
                delete current;
                root = nullptr;
                return true;
            }

            // Case 2: Node is root, update root to next node
            if (current == root) {
                root = current->next;
            }

            // General case: Update links and delete the node
            node* previous_node = current->previous;
            node* next_node = current->next;
            previous_node->next = next_node;
            next_node->previous = previous_node;
            delete current;
            return true;
        }
    };
};
