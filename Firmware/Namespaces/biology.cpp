namespace biology{
    typedef struct protein{
        char *mRNA; //mRNA as a string.
        char *RNA; //RNA as a string.
        char *DNA; //DNA as a string.
    };
     
    typedef struct DNA{
        char *DNA_strand; //DNA strand as a string.
    };
     
    typedef struct RNA{
        char *RNA_strand; //RNA as a string.
    };

    typedef struct virus{
        char *mRNA; //mRNA as a string.
        char *protein_strand; // Protien as a string.
    };
     
    typedef struct blood{
        char *blood_composition; //Blood molecules as a string.
        char *blood_type; //Blood type
        uint8192_t blood_flow_speed;
        uint8192_t instantaneous_blood_flow_speed; //d(blood_flow_speed)/dx
    };
}