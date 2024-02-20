#include <iostream>
#include <string>
#include <algorithm> 
#include <vector>


class big_integer {
private:
    std::string number_;
    std::vector<char> numbers;
public:
    
    big_integer(std::string number) : number_(number){
        for (int i = 0; i < number.size(); i++) {
            numbers.push_back(number[i]);
        }
    }

    big_integer(const big_integer& other)
        : big_integer(other.number_) {}
 
    big_integer& operator=(const big_integer& other) 
    {
        return *this = big_integer(other);
    }

    big_integer(big_integer&& other) noexcept
    {
        number_ = other.number_;
        other.number_.clear();
    }

    big_integer& operator=(big_integer&& other) noexcept 
    {
        number_ = other.number_;
        other.number_.clear();
        return *this;
    }
    ~big_integer() {
        number_.clear();
    }

    big_integer operator + (big_integer other)
    {
        std::string new_number_;
        std::vector<char> new_num;
        int tmp = 0;
            for (int i = number_.size() - 1 , j = other.number_.size() - 1; i >= 0 || j >= 0; i--, j--) {
                if (j < 0) {
                    new_num.push_back(tmp + number_[i] - 48);
                    tmp = 0;
                }
                else if (i < 0) {
                    new_num.push_back(tmp + other.number_[j] - 48);
                    tmp = 0;
                }

                else {
                    if (tmp + number_[i] - 48 + other.number_[j] - 48 >= 10 && i != 0 || tmp + number_[i] - 48 + other.number_[j] - 48 >= 10 && j != 0) {
                        new_num.push_back(tmp + number_[i] - 48 + other.number_[j] - 48 - 10);
                        tmp = 1;
                    }
                    else {
                        new_num.push_back(tmp + number_[i] - 48 + other.number_[j] - 48);
                        tmp = 0;
                    }
                }
            }
        
        reverse(new_num.begin(), new_num.end() );
        
        for (int i = 0; i < new_num.size(); i++) {
            new_number_ += std::to_string (new_num[i]);
        }
        return new_number_;
      
    }

    big_integer operator * ( int other) {
        std::string new_number_;
        std::vector<char> new_num;
        int tmp = 0;
        for (int i = number_.size() - 1; i >= 0 ; i--) {
            if (tmp + (number_[i] - 48) * other >= 10 && i != 0 ) {
                new_num.push_back(tmp + (number_[i] - 48) * other - 10);
                tmp = 1;
            }
            else {
                new_num.push_back(tmp + (number_[i] - 48) * other);
                tmp = 0;
            }
        }

        reverse(new_num.begin(), new_num.end());

        for (int i = 0; i < new_num.size(); i++) {
            new_number_ += std::to_string(new_num[i]);
        }

        return new_number_;

    }

    void Show() {
        std::cout << number_;
    }

};


int main()
{

    auto number1 = big_integer("65432");
    auto number2 = big_integer("298653");

    auto result = number1 + number2;
    auto result1 = number1 * 3;
 
    result.Show();
    std::cout << "\n";
    result1.Show();
           
    return 0;
}