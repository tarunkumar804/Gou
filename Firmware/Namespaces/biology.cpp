namespace biology{
     typedef struct protein{
         char *mRNA;
         char *RNA;
         char *DNA
     };
     
     typedef struct DNA{
         char *DNA_strand;
     };
     
     typedef struct RNA{
         char *RNA_strand;
     };

     typedef struct virus{
         char *mRNA;
         char *protein_strand;
     };
     
     typedef struct blood{
         char *blood_composition;
         char *blood_type;
         uint8192_t blood_flow_speed;
         uint8192_t instantaneous_blood_flow_speed;
     };
}