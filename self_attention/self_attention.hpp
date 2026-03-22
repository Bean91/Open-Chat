#include "../utility/utility.hpp"

namespace openchat {
    class selfAttention {
        private:
            utility::matrix wq;
            utility::matrix wk;
            utility::matrix wv;
            
            utility::matrix q;
            utility::matrix k;
            utility::matrix v;
        public:
            selfAttention(utility::matrix wq, utility::matrix wk, utility::matrix wv) {
                this->wq = wq;
                this->wk = wk;
                this->wv = wv;
            }
            
            utility::matrix attention(utility::matrix X, size_t xn, size_t xm, size_t d) {
                this->q = utility::dot(X, xn, xm, this->wq, d, d);
                this->k = utility::dot(X, xn, xm, this->wk, d, d);
                this->v = utility::dot(X, xn, xm, this->wv, d, d);
                
                return utility::dot(utility::softmax(utility::scalar_div(utility::dot(this->q, utility::transpose(this->k, xn, xm), xn, xm)), std::sqrt(d)), this->v, xn, xm); 
            }
    };
}