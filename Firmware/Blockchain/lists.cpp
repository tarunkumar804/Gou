using namespace data;

class list{
    class circular_linked_list{

        protected:
            node *root;

        public:

            circular_linked_list(node* starting_node)
            {
                root = starting_node;
            }
            node* create_and_add_node(node *previous_node, char *contents_to_insert){

                node *new_node = new node();
            
                new_node -> contents = contents_to_insert;
                new_node -> next = NULL;
                new_node -> previous = previous_node;
                new_node -> loopback = root;
                return new_node;
            }
    
            node* node_you_want_to_traverse_until (node *node_to_traverse_until)
            {
                node *current = root;
                while (current != node_to_traverse_until)
                    current = current -> next;
                return current;
            }

            bool delete_node(node *node_to_delete)
            {
                node *current = root;
                node *previous_node, *next_node;
                
                while (current != node_to_delete)
                    current = current -> next;
                if (current == NULL)
                    return false;
                
                else if (current == node_to_delete)
                {
                    if (current -> next == NULL)
                    {
                        previous_node = current -> previous;
                        previous_node -> loopback = root;
                        delete current;
                    }

                    else{
                        
                        previous_node = current -> previous;
                        next_node = current -> next;
                        delete current;
                        previous_node -> next = next_node;
                        next_node -> previous = previous_node;
                    }
                }
                return true;
            }
    };
};