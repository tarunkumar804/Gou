namespace particle_physics{
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