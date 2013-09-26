#ifndef EXT__EXPECT_H
#define EXT__EXPECT_H

#include <sstream>

template<typename T>
class ExpectValue {
    typedef T value_type ;
public:
    ExpectValue(T& value, Spec *pSpec, std::string file, int line) {
        this->file = file;
        this->line = line;
        this->pSpec = pSpec;
        this->value = &value;
        this->pSpec->ExpectSum++;
    }
    void ToBe(T& value) {
        if(*(this->value) != value) {
            this->pSpec->ErrorSum++;
            std::stringstream  stream1;
            std::stringstream  stream2;
            stream1 << file << " (" << line << ")";
            stream2 << "expect " << *(this->value) << " tobe " << value;
            pSpec->AddError(stream1.str());
            pSpec->AddError(stream2.str());
        }
    }
    void ToBeTruthy() {
        return ToBe(true);
    }
    void ToBeFalsy() {
        return ToBe(fals);
    }
private:
    std::string file;
    int line;
    Spec *pSpec;
    T* value;
};

#define Expect(value)  expect(value,__FILE__,__LINE__)
template<typename T>
ExpectValue<T> expect(T& value, std::string file, int line) {
	return ExpectValue<T>(value, Spec::getInstance(), file, line);
}

#endif