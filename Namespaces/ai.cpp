namespace ai {
    typedef struct markov_node{
        char *name_of_node;
        uint8192_t number_of_nodes;
        uint8192_t addresses_of_transitions [number_of_nodes];
    };
    
    typedef struct markov_model{
        uint8192_t number_of_nodes;
        markov_node nodes [number_of_nodes];
    };
}