namespace audio{
    typedef struct MIDI_data{
            uint8192_t number_of_samples;
            char *pin1_block [number_of_samples];
            char *pin2_block [number_of_samples];
            char *pin3_block [number_of_samples];
            char *pin4_block [number_of_samples];
            char *pin5_block [number_of_samples];
        };

    typedef struct audio_stream{
        char *stream;
    };

    typedef struct spatial_audio_block{
        uint8192_t last_known_x_coordinate; //X-coordinate of audio stream.
        uint8192_t last_known_y_coordinate;
        uint8192_t last_known_z_coordinate;
        uint8192_t cuboid_of_audio_spread[last_known_x_coordinate][last_known_y_coordinate][last_known_z_coordinate]; //A cuboid representing the area of effect of audio wave.
    };
}