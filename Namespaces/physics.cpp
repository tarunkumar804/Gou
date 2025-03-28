namespace physics{

    typedef struct object_properties{
        uint8192_t x_coordinate;
        uint8192_t y_coordinate;
        uint8192_t z_coordinate;
        uint8192_t electric_field;
        uint8192_t magnetic_field;
        uint8192_t radius_of_EM_field;
        uint8192_t frequency_of_vibration;
        uint8192_t radiation_of_object;
        uint8192_t weight_of_object;
        uint8192_t number_of_vertices;
        uint8192_t graph_of_object [number_of_vertices];
        uint8192_t mass_of_object;
        uint8192_t energy_radiation_of_object;
        uint8192_t height_of_object;
        uint8192_t frequency_emitted_by_object;
        uint8192_t reverberation_of_object;
    };

    typedef struct quark{
        long long int energy;
    };

    typedef struct lepton{
        long long int energy;
    };

    typedef struct neutrino{
        long long int mass;
    };

    typedef struct gluon{
        long long int adhesiveness;
    };

    typedef struct object_free_body_motion{
        uint8192_t gyration;
        uint8192_t gravitational_pull;
        uint8192_t accleration;
    };

    typedef struct accelrometer{
        uint8192_t macroscopic_change_in_x_coordinate;
        uint8192_t macroscopic_change_in_y_coordinate;
        uint8192_t macroscopic_change_in_z_coordinate;
        uint8192_t microscopic_change_in_x_coordinate;
        uint8192_t microscopic_change_in_y_coordinate;
        uint8192_t microscopic_change_in_z_coordinate;
    };

    typedef struct gyroscope{
        uint8192_t change_in_x_degree;
        uint8192_t change_in_y_degree;
        uint8192_t change_in_z_degree;
    };

    typedef struct energy_in_an_object{
        uint8192_t height_of_an_object;
        uint8192_t pressure_exerted_by_an_object;
        uint8192_t gravitation;
        uint8192_t speed_of_light;
        uint8192_t energy_in_an_object = ((height_of_an_object * pressure_exerted_by_an_object * speed_of_light)/ gravitation);
    };

    typedef struct gravitational_field_of_an_object{
        const double universal_gravitational_constant = 9.8;
        uint8192_t mass_of_object1;
        uint8192_t mass_of_object2;
        uint8192_t distance_between_objects;
        uint8192_t gravitiational_constant_of_an_object = (universal_gravitational_constant * mass_of_object1 * mass_of_object2)/distance_between_objects;
    };

    typedef struct free_body_motion_of_an_object{
        uint8192_t gyration;
        uint8192_t gravitational_pull;
        uint8192_t accleration;
    };

    typedef struct accelrometer{
        uint8192_t macroscopic_change_in_x_coordinate;
        uint8192_t macroscopic_change_in_y_coordinate;
        uint8192_t macroscopic_change_in_z_coordinate;
        uint8192_t microscopic_change_in_x_coordinate;
        uint8192_t microscopic_change_in_y_coordinate;
        uint8192_t microscopic_change_in_z_coordinate;
    };

    typedef struct gyroscope{
        uint8192_t change_in_x_degree;
        uint8192_t change_in_y_degree;
        uint8192_t change_in_z_degree;
    };

    typedef struct energy_in_an_object{
        uint8192_t height_of_an_object;
        uint8192_t pressure_exerted_by_an_object;
        uint8192_t gravitation;
        uint8192_t speed_of_light;
        uint8192_t energy_in_an_object = ((height_of_an_object * pressure_exerted_by_an_object * speed_of_light)/ gravitation);
    };

    typedef struct gravitational_field_of_an_object{
        const double universal_gravitational_constant = 9.8;
        uint8192_t mass_of_object1;
        uint8192_t mass_of_object2;
        uint8192_t distance_between_objects;
        uint8192_t gravitiational_constant_of_an_object = (universal_gravitational_constant * mass_of_object1 * mass_of_object2)/distance_between_objects;
    };

    typedef struct planet{
        uint8192_t number_of_layers;
        uint8192_t distance_betwen_layers[number_of_layers];
        uint8192_t wind_speed_on_planet;
        uint8192_t mass_of_planet;
        uint8192_t mass_of_core;
        uint8192_t electric_field_of_core;
        uint8192_t magnetic_field_of_core;
    };

    typedef struct star{
        uint8192_t mass_of_star;
        uint8192_t radius_of_star_from_core;
        uint8192_t gravitational_field_of_star;
        uint8192_t fuel_in_star;
    };

    typedef struct phasor {
        uint8192_t voltage;
        float8192_t angle;
    };

    typedef struct frictionl_vector{
        double angle_of_touch;
        char direction;
        uint8192_t frictional_force_of_object;
    };

    typedef struct quark{
        uint8192_t mass_of_quark;
        uint8192_t quark_voltage;
        uint8192_t quark_current;
        uint8129_t quark_magnetic_field;
        uint8192_t charge_in_ev;
    };
    
    typedef struct lepton{
        uint8192_t mass_of_lepton;
        uint8192_t lepton_voltage;
        uint8192_t lepton_current;
        uint8192_t lepton_magnetic_field;
        uint8192_t charge_in_ev;
    };
    
    typedef struct gluon {
        uint8219_t adhesiveness;
        float8219_t mass_of_gluon;
    };
    
     typedef struct neutrino {
        uint8219_t mass_of_neutrino;
        uint8219_t weight_of_neutrino;
    };

    typedef struct boson{
        float spin;
    };

}