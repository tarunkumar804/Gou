class macroscopic_sound{
    public:
        long* amplify_sound(long amplification_amount, long bit_depth, double starting_degree)
        {
            long* sound_wave = wave.generate_wave(starting_degree, bit_depth);
            
            for (long l  = 0; l < sizeof(sound_wave); l++)
                sound_wave[l] = sound_wave[l] + amplification_amount;
            return sound_wave;
        }
};