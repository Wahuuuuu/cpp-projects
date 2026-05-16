#ifndef TUPLE_H
#define TUPLE_H

using namespace std;

template <class T>
class Tuple 
{
public:
    Tuple(const T& line, const T& word);
    virtual ~Tuple();

    void setLine(const T& line) const;
    void setWord(const T& word) const;

    const T& getLine() const;
    const T& getWord() const;

    bool operator<(const Tuple<T>& other) const;
    bool operator==(const Tuple<T>& other) const;

private:
    T line;
    T word;
};


// constructor and destructor
template <class T>
Tuple<T>::Tuple(const T& line, const T& word) {
    this->line = line;
    this->word = word;
}

template <class T>
Tuple<T>::~Tuple() {
}

// getters and setters
template <class T>
void Tuple<T>::setLine(const T& line) const { this->line = line; }

template <class T>
void Tuple<T>::setWord(const T& word) const { this->word = word; }


template <class T>
const T& Tuple<T>::getLine() const { return this->line; }

template <class T>
const T& Tuple<T>::getWord() const { return this->word; }


// overrides

/**
 * @brief Returns whether the left value is smaller than the right value, 
 * 
 * Lvalue is smaller than rvalue if : lvalue.line < rvalue.line, or
 *                                    (lvalue.line == rvalue.line) && (lvalue.word < rvalue.word)
 * 
 * @return True if the left value is smaller than the right value, false otherwise.
 */
template <class T>
bool Tuple<T>::operator<(const Tuple<T>& other) const {
    if (this.line < other.getLine()) return true;
    if ((this.line == other.getLine()) && (this.word < other.getWord())) return true;

    return false;
}


/**
 * @brief Retruens whether both tuples are equals.
 * 
 * lvalue and rvalue are equals if (lvalue.line == rvalue.line) && (lvalue.word == rvalue.word)
 * 
 * @return True if both tuples are equals, false otherwise.
 */
template <class T>
bool Tuple<T>::operator==(const Tuple<T>& other) const {
    return ((this.line == other.getLine()) && (this.word == other.getWord()));
}

#endif // TUPLE_H