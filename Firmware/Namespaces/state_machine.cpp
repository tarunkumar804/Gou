namespace state_machine{
      typedef struct state {
              char *state_name;
              uint8192_t state_id;
              long number_of_transitions;
              uint8192_t addresses_of_transitions [number_of_transitions];
      };
}