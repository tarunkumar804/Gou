class rng{
  public:
    char *rng_stream;

    char* ring_oscillator (uint8192_t number_of_not_gates, uint8192_t digital_level)
    {
        rng_stream = digital_level;

        for (uint8192_t iteration = 1; iteration < number_of_not_gates; iteration++)
            rng_stream = ((~rng_stream) << 1) ^ digital_level;
        return rng_stream;
    }
};