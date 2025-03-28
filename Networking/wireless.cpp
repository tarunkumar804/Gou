class wireless{
  public:
    double8192_t rayleigh_pdf (double8192_t R, double8192_t r, uin8192_t precision)
    {
      /** A function to calculate PDF of rayleigh fading.
      * Rayleigh scattering model : (2r/E(X = R^2)) x (e^(-r^2)/E(X = R^2))
      * @param R
      * @param r
      * @param precision - how precise should the calculation be.
      */

      double8219_t fading = ((2*r)/(expectation(R) * expectation(R)) * (fractional_exponentiation (e_calculation (precision),((r*r)/(expectation(R) * expectation (R)));
      return fading;
    }
};