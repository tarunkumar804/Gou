namespace astrology{
   //Rahu and Ketu do not exist anymore.

   typedef struct personal_information{
        char *name; // Nsme of the person.
        int day; // Day of the birth.
        int month; // Month of the birth.
        int year; // Year of birth.
        int hour; // Hour of birth.
        int month; // Month of birth.
        int second; // Second of birth.
        double latitude; //Latitude of birth.
        double longitude; //Longitude of birth.
   };
   
   typedef struct sun{
        double degrees;
        double minutes;
        double seconds;
   };
   
   typedef struct moon{
        double degrees;
        double minutes;
        double seconds;
   };
   
   typedef struct mercury{
        double degrees;
        double minutes;
        double seconds;
   };
   
   typedef struct venus{
        double degrees;
        double minutes;
        double seconds;
   };

   typedef struct mars{
        double degrees;
        double minutes;
        double seconds;
   };

   typedef struct jupiter{
        double degrees;
        double minutes;
        double seconds;
   };

   typedef struct saturn{
        double degrees;
        double minutes;
        double seconds;
   };

   typedef struct uranus{
        double degrees;
        double minutes;
        double seconds;
   };

   typedef struct neptune{
        double degrees;
        double minutes;
        double seconds;
   };

   typedef struct pluto{
        double degrees;
        double minutes;
        double seconds;
   };
   
   typedef struct ascendant{
        double degrees;
        double minutes;
        double seconds;
   };
}