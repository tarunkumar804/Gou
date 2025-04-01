class wireless{
  public:
    double rayleigh_pdf (double R, double r, uint8192_t precision)
    {
      /** A function to calculate PDF of rayleigh fading.
      * Rayleigh scattering model : (2r/E(X = R^2)) x (e^(-r^2)/E(X = R^2))
      * @param R
      * @param r
      * @param precision - how precise should the calculation be.
      */

      double fading = ((2*r)/(expectation(R) * expectation(R)) * (negative_exponentiation (e_calculation (precision),((r*r)/(expectation(R) * expectation (R))))));
      return fading;
    }
};