// Mikolaj Suchan
#include <iostream>
#include <cstdarg>

using namespace std;

class POLYNOMIAL {
    public:
        int degree;
        int* coeffs;
        static int overloaded;

        int cnt_gcd(int a, int b) {
            if (a < 0)
                a = -a;
            if (b < 0)
                b = -b;

            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }

        int gcd_array() {
            int gcd = 0;
            for (int i = 0; i <= degree; ++i) {
                if (coeffs[i] == 0)
                    continue;
                if (gcd == 0) {
                    if (coeffs[i] < 0)
                        gcd = -coeffs[i];
                    else
                        gcd = coeffs[i];
                }
                else
                    gcd = cnt_gcd(gcd, coeffs[i]);
            }
            return gcd;
        }

        void remove_zeroes() {
            int newDegree = 0;
            for (int i = degree; i >= 0; --i) {
                if (coeffs[i] != 0) {
                    newDegree = i;
                    break;
                }
            }

            degree = newDegree;
            int* newCoeffs = new int[degree + 1];
            for (int i = 0; i <= degree; ++i) {
                newCoeffs[i] = coeffs[i];
            }
            delete[] coeffs;
            coeffs = newCoeffs;
        }

        POLYNOMIAL(){
            degree = 0;
            coeffs = new int[1];
            coeffs[0] = 0;
            overloaded++;
        }

        POLYNOMIAL(int deg, ...) {
            degree = deg;
            coeffs = new int[degree + 1];
            
            va_list args;
            va_start(args, deg);
            for (int i = 0; i <= degree; ++i) {
                coeffs[i] = va_arg(args, int);
            }
            va_end(args);

            remove_zeroes();
            int gcd = gcd_array();
            if (gcd == 0)
                gcd = 1;
            for (int i = 0; i <= degree; ++i) {
                coeffs[i] /= gcd;
            }
            overloaded++;
        }

        POLYNOMIAL(const POLYNOMIAL& other) {
            degree = other.degree;
            coeffs = new int[degree + 1];
            for (int i = 0; i <= degree; ++i) {
                coeffs[i] = other.coeffs[i];
            }
            overloaded++;
        }

        ~POLYNOMIAL() {
            overloaded--;
            delete[] coeffs;
        }

        friend ostream& operator<<(ostream& stream, const POLYNOMIAL& P) {
            stream << "( ";
            for (int i = 0; i <= P.degree; ++i) {
                stream << P.coeffs[i];
                if (i < P.degree)
                    stream << ", ";
            }
            stream << " )";
            return stream;
        }

        friend istream& operator>>(istream& stream, POLYNOMIAL& P) {
            stream >> P.degree;
            delete[] P.coeffs;
            P.coeffs = new int[P.degree + 1];
            for (int i = 0; i <= P.degree; ++i) {
                stream >> P.coeffs[i];
            }

            P.remove_zeroes();
            int gcd = P.gcd_array();
            if (gcd == 0)
                gcd = 1;
            for (int i = 0; i <= P.degree; ++i) {
                P.coeffs[i] /= gcd;
            }

            return stream;
        }

        POLYNOMIAL& operator=(const POLYNOMIAL& P) {
            if (this == &P)
                return *this;
            
            delete[] coeffs;
            degree = P.degree;
            coeffs = new int[degree + 1];
            for (int i = 0; i <= degree; ++i) {
                coeffs[i] = P.coeffs[i];
            }
            return *this;
        }

        POLYNOMIAL operator+(const POLYNOMIAL& P) {
            int maxDegree = degree;
            if (P.degree > maxDegree)
                maxDegree = P.degree;
            
            POLYNOMIAL result;
            delete[] result.coeffs;
            result.degree = maxDegree;
            result.coeffs = new int[maxDegree + 1];

            for (int i = 0; i <= maxDegree; ++i) {
                int a = 0;
                int b = 0;
                if (i <= degree)
                    a = coeffs[i];
                if (i <= P.degree)
                    b = P.coeffs[i];
                result.coeffs[i] = a + b;
            }

            result.remove_zeroes();
            int gcd = result.gcd_array();
            if (gcd == 0)
                gcd = 1;
            for (int i = 0; i <= result.degree; ++i) {
                result.coeffs[i] /= gcd;
            }
            
            return result;
        }

        POLYNOMIAL operator-() {
            POLYNOMIAL result = *this;
            for (int i = 0; i <= result.degree; ++i) {
                result.coeffs[i] = -result.coeffs[i];
            }
            return result;
        }

        POLYNOMIAL operator-(const POLYNOMIAL& P) {
            int maxDegree = degree;
            if (maxDegree < P.degree)
                maxDegree = P.degree;
           
            POLYNOMIAL result;
            delete[] result.coeffs;
            result.degree = maxDegree;
            result.coeffs = new int[maxDegree + 1];

            for (int i = 0; i <= maxDegree; ++i) {
                int a = 0;
                int b = 0;
                if (i <= degree)
                    a = coeffs[i];
                if (i <= P.degree)
                    b = P.coeffs[i];
                result.coeffs[i] = a - b;
            }

            result.remove_zeroes();
            int gcd = result.gcd_array();
            if (gcd == 0)
                gcd = 1;
            for (int i = 0; i <= result.degree; ++i) {
                result.coeffs[i] /= gcd;
            }
            
            return result;
        }

        POLYNOMIAL operator*(const POLYNOMIAL& P) {
            int newDegree = degree + P.degree;

            POLYNOMIAL result;
            delete[] result.coeffs;
            result.degree = newDegree;
            result.coeffs = new int[result.degree + 1];
            for (int i = 0; i <= result.degree; ++i) {
                result.coeffs[i] = 0;
            }

            for (int i = 0; i <= degree; ++i) {
                for (int j = 0; j <= P.degree; ++j) {
                    result.coeffs[i + j] += coeffs[i] * P.coeffs[j];
                }
            }

            result.remove_zeroes();
            int gcd = result.gcd_array();
            if (gcd == 0)
                gcd = 1;
            for (int i = 0; i <= result.degree; ++i) {
                result.coeffs[i] /= gcd;
            }

            return result;
        }

        POLYNOMIAL& operator+=(const POLYNOMIAL& P) {
            *this = *this + P;
            return *this;
        }

        POLYNOMIAL& operator-=(const POLYNOMIAL& P) {
            *this = *this - P;
            return *this;
        }

        POLYNOMIAL& operator*=(const POLYNOMIAL& P) {
            *this = *this * P;
            return *this;
        }

        POLYNOMIAL& operator++() {
            for (int i = 0; i <= degree; ++i) {
                coeffs[i]++;
            }
            
            remove_zeroes();
            int gcd = gcd_array();
            if (gcd == 0)
                gcd = 1;
            for (int i = 0; i <= degree; ++i) {
                coeffs[i] /= gcd;
            }

            return *this;
        }

        POLYNOMIAL operator++(int) {
            POLYNOMIAL temp = *this;
            ++(*this);
            return temp;
        }

        POLYNOMIAL& operator--() {
            for (int i = 0; i <= degree; ++i) {
                coeffs[i]--;
            }
            
            remove_zeroes();
            int gcd = gcd_array();
            if (gcd == 0)
                gcd = 1;
            for (int i = 0; i <= degree; ++i) {
                coeffs[i] /= gcd;
            }

            return *this;
        }

        POLYNOMIAL operator--(int) {
            POLYNOMIAL temp = *this;
            --(*this);
            return temp;
        }

        POLYNOMIAL operator>>(int times) {
            if (times < 0) {
                return POLYNOMIAL();
            }
            
            if (degree == 0 && coeffs[0] == 0) {
                return POLYNOMIAL();
            }

            int newDegree = degree + times;
            POLYNOMIAL result;
            delete[] result.coeffs;
            result.degree = newDegree;
            result.coeffs = new int[newDegree + 1];
            for (int i = 0; i < times; ++i) {
                result.coeffs[i] = 0;
            }
            for (int i = 0; i <= degree; ++i) {
                result.coeffs[i + times] = coeffs[i];
            }
            
            result.remove_zeroes();
            int gcd = result.gcd_array();
            if (gcd == 0)
                gcd = 1;
            for (int i = 0; i <= newDegree; ++i) {
                result.coeffs[i] /= gcd;
            }

            return result;
        }

        POLYNOMIAL operator<<(int times) {
            if (times > degree || times < 0) {
                return POLYNOMIAL();
            }

            if (degree == 0 && coeffs[0] == 0) {
                return POLYNOMIAL();
            }

            int newDegree = degree - times;
            POLYNOMIAL result;
            delete[] result.coeffs;
            result.degree = newDegree;
            result.coeffs = new int[newDegree + 1];
            for (int i = 0; i <= newDegree; ++i) {
                result.coeffs[i] = coeffs[i + times];
            }
            
            result.remove_zeroes();
            int gcd = result.gcd_array();
            if (gcd == 0)
                gcd = 1;
            for (int i = 0; i <= newDegree; ++i) {
                result.coeffs[i] /= gcd;
            }

            return result;
        }

        POLYNOMIAL operator>>=(int times) {
            *this = *this >> times;
            return *this;
        }

        POLYNOMIAL operator<<=(int times) {
            *this = *this << times;
            return *this;
        }

        POLYNOMIAL operator/(const POLYNOMIAL& P) {
            if (P.degree == 0 && P.coeffs[0] == 0) {
                return POLYNOMIAL();
            }

            if (degree < P.degree) {
                return POLYNOMIAL();
            }

            int newDegree = degree - P.degree;
            POLYNOMIAL result;
            delete[] result.coeffs;
            result.degree = newDegree;
            result.coeffs = new int[newDegree + 1];
            for (int i = 0; i <= newDegree; ++i) {
                result.coeffs[i] = 0;
            }

            POLYNOMIAL temp = *this;
            int* divisors = new int[newDegree + 1];
            for (int i = 0; i <= newDegree; ++i)
                divisors[i] = 1;
            
            for (int i = degree, j = newDegree; i >= P.degree; --i, --j) {
                if (temp.coeffs[i] == 0)
                    continue;

                int lcm = temp.coeffs[i] * P.coeffs[P.degree];
                lcm /= cnt_gcd(temp.coeffs[i], P.coeffs[P.degree]);
                int div = lcm / temp.coeffs[i];
                if (div < 0)
                    div = -div;
                for (int k = 0; k <= i; ++k) {
                    temp.coeffs[k] *= div;
                }

                for (int k = j; k >= 0; --k) {
                    divisors[k] *= div;
                }

                result.coeffs[j] = temp.coeffs[i] / P.coeffs[P.degree];
                div = result.coeffs[j];
                for (int k = i, h = P.degree; h >= 0; --k, --h) {
                    temp.coeffs[k] -= div * P.coeffs[h];
                }
            }
            int lcm = 1;
            for (int i = 0; i <= newDegree; ++i) {
                lcm *= divisors[i] / cnt_gcd(lcm, divisors[i]);
            }

            for (int i = 0; i <= newDegree; ++i) {
                result.coeffs[i] *= lcm / divisors[i];
            }

            result.remove_zeroes();
            int gcd = result.gcd_array();
            if (gcd == 0)
                gcd = 1;
            for (int i = 0; i <= newDegree; ++i) {
                result.coeffs[i] /= gcd;
            }
            delete[] divisors;
            return result;
        }

        POLYNOMIAL operator%(const POLYNOMIAL& P) {
            if ((degree == 0 && coeffs[0] == 0) || (P.degree == 0 && P.coeffs[0] == 0)) {
                return *this;
            }

            if (degree < P.degree) {
                return *this;
            }
            
            int newDegree = degree - P.degree;
            POLYNOMIAL result;
            delete[] result.coeffs;
            result.degree = newDegree;
            result.coeffs = new int[newDegree + 1];
            for (int i = 0; i <= newDegree; ++i) {
                result.coeffs[i] = 0;
            }

            POLYNOMIAL temp = *this;
            int* divisors = new int[newDegree + 1];
            for (int i = 0; i <= newDegree; ++i)
                divisors[i] = 1;
            
            for (int i = degree, j = newDegree; i >= P.degree; --i, --j) {
                if (temp.coeffs[i] == 0)
                    continue;

                int lcm = temp.coeffs[i] * P.coeffs[P.degree];
                lcm /= cnt_gcd(temp.coeffs[i], P.coeffs[P.degree]);
                int div = lcm / temp.coeffs[i];
                if (div < 0)
                    div = -div;

                for (int k = 0; k <= i; ++k) {
                    temp.coeffs[k] *= div;
                }

                for (int k = j; k >= 0; --k) {
                    divisors[k] *= div;
                }
                result.coeffs[j] = temp.coeffs[i] / P.coeffs[P.degree];
                div = result.coeffs[j];
                for (int k = i, h = P.degree; h >= 0; --k, --h) {
                    temp.coeffs[k] -= div * P.coeffs[h];
                }
            }

            int lcm = 1;
            for (int i = 0; i <= newDegree; ++i) {
                lcm *= divisors[i] / cnt_gcd(lcm, divisors[i]);
            }

            for (int i = 0; i <= newDegree; ++i) {
                result.coeffs[i] *= lcm / divisors[i];
            }

            delete[] divisors;
            delete[] result.coeffs;
            result.degree = P.degree - 1;
            if (result.degree < 0) {
                result.degree = 0;
                result.coeffs = new int[1];
                result.coeffs[0] = 0;
                return result;
            }

            result.coeffs = new int[result.degree + 1];
            for (int i = 0; i <= result.degree; ++i) {
                result.coeffs[i] = temp.coeffs[i];
            }
            result.remove_zeroes();
            int gcd = result.gcd_array();
            if (gcd == 0)
                gcd = 1;
            for (int i = 0; i <= result.degree; ++i) {
                result.coeffs[i] /= gcd;
            }
            return result;
        }

        POLYNOMIAL& operator/=(const POLYNOMIAL& P) {
            *this = *this / P;
            return *this;
        }

        POLYNOMIAL& operator%=(const POLYNOMIAL& P) {
            *this = *this % P;
            return *this;
        }
};

int POLYNOMIAL::overloaded = 0;

bool operator==(const POLYNOMIAL& P1, const POLYNOMIAL& P2) {
    if (P1.degree != P2.degree)
        return false;
    for (int i = 0; i <= P1.degree; ++i) {
        if (P1.coeffs[i] != P2.coeffs[i])
            return false;
    }
    return true;
}

bool operator!=(const POLYNOMIAL& P1, const POLYNOMIAL& P2) {
    return !(P1 == P2);
}

bool operator<(const POLYNOMIAL& P1, const POLYNOMIAL& P2) {
    if (P1.degree < P2.degree)
        return true;
    if (P1.degree > P2.degree)
        return false;
    for (int i = 0; i <= P1.degree; ++i) {
        if (P1.coeffs[i] < P2.coeffs[i])
            return true;
        if (P1.coeffs[i] > P2.coeffs[i])
            return false;
    }
    return false;
}

bool operator<=(const POLYNOMIAL& P1, const POLYNOMIAL& P2) {
    return (P1 < P2 || P1 == P2);
}

bool operator>(const POLYNOMIAL& P1, const POLYNOMIAL& P2) {
    return !(P1 <= P2);
}

bool operator>=(const POLYNOMIAL& P1, const POLYNOMIAL& P2) {
    return !(P1 < P2);
}
