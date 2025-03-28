namespace ml{
   typedef struct perceptron_network{
        uint8192_t number_of_feed_forward_units;
        uint8192_t number_of_hidden_layers;
        uint8192_t number_of_hidden_units;
        uint8192_t feed_forward_vector[number_of_feed_forward_units+1]; // A vector to store the feed-forward layer.
        uint8192_t hidden_matrix[number_of_units+1][number_of_hidden_layers]; //A matrix to store the hidden layers.
   };
   
   typedef struct reinforcement {
        long long int reward;
        long long int negative_reward;
   };

   typedef struct cluster {
       uint8192_t number_of_classification_goals;
       uint8192_t number_of_attributes;
       uint8192_t number_of_clusters;
       uint8192_t number_of_data_points;
       uint8192_t classification_matrix [number_of_classsification_goals][number_of_attributes];
       uint8192_t clusters [number_of_clusters][number_of_data_points];
   };
   
   typedef struct leaf{
       uint8192_t number_of_stems;
       uint8192_t stem_matrix [number_of_stems];
       char *data;
   };

   typedef struct vector{
       uint8192_t length_of_vector;
       uint8192_t vector[length_of_vector];
   };
   
   typedef struct regressor{
       uint8192_t length_of_regression_array;
       uint8192_t regressions[length_of_regression_array];
   };
   
   typedef struct gradients{
       uint8192_t number_of_gradients;
       uint8192_t gradients [number_of_gradients];
   };

   typedef struct transformer{
       uint8192_t number_of_vectors;
       uint8192_t length_of_vectors;
       uint8192_t number_of_parameters;
       uint8192_t number_of_tuners;
       uint8192_t transformer [number_of_vectors][length_of_vector];
       uint8192_t parameters [number_of_parameters][number_of_tuners];
   };

   typedef struct logical{
        
   };
}