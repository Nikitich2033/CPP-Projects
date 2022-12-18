#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H


// Do not add any #include statements to this file

class SudokuSquareSet {

  private:

    unsigned int setValues;

    int setSize;

  public:



    SudokuSquareSet(){

      setValues = 0;
      setSize = 0;

    }


    class SudokuSquareSetIterator{

    private:
      unsigned int CopyOfSetValues;
      int currentPos;

    public:

     SudokuSquareSetIterator(int currentPosition, unsigned int setValuesIn)
                  : currentPos(currentPosition), CopyOfSetValues(setValuesIn) {}

     SudokuSquareSetIterator(unsigned int setValuesIn): CopyOfSetValues(setValuesIn){

       currentPos = 1;

     }

     SudokuSquareSetIterator begin(){

          if(CopyOfSetValues==0)// for num==0 there is zero set bit
           {
              return 0;
           }
           else
           {
             int pos = 1;
             // counting the position of first set bit
             for (int i = 0; i < 32; i++) {
                 if (!(CopyOfSetValues & (1 << i)))
                     pos++;
                 else
                     break;
             }

             return SudokuSquareSetIterator(pos,CopyOfSetValues);
           }
      }

      SudokuSquareSetIterator end() const{
        unsigned int temp = CopyOfSetValues;

        if (CopyOfSetValues == 0){
            return SudokuSquareSetIterator(0);
        }

        unsigned r = 1;

        while (temp >>= 1) {
            r++;
        }

        //std::cout << "Size of R: "<<  r << '\n';
        return SudokuSquareSetIterator(r + 1,temp);

      }

      void operator++(){


        bool valueFound = false;

        while (valueFound != true && currentPos < *end()) {
          ++currentPos;
          if (CopyOfSetValues & (1 << (currentPos - 1))){
            valueFound = true;
          }
        }


        //std::cout << "Position: "<< currentPos << '\n' << std::endl;


      }

      int operator*() {

          return currentPos;

      }

      bool operator==(const SudokuSquareSetIterator& input) {

        return currentPos == input.currentPos;

      }

      bool operator!=(const SudokuSquareSetIterator& input) {

        return !(currentPos == input.currentPos);

      }

    };


    int size() const{
      unsigned int temp = setValues;
      unsigned int count = 0;

      while (temp) {
        count += temp & 1;
        temp >>= 1;
      }

      return count;

    }

    void clear(){

      setValues = 0;

    }

    bool operator==(SudokuSquareSet& rhs){
      if (setValues == rhs.setValues) {
        return true;
      }
      else{
        return false;
      }
    }

    bool operator!=(SudokuSquareSet& rhs){
      return !(setValues == rhs.setValues);
    }


    SudokuSquareSetIterator insert(int value){

      setValues ^= (-1 ^ setValues) & (1 << value - 1);
      return SudokuSquareSetIterator(value - 1,setValues);

    }

    SudokuSquareSetIterator find(int value){
        unsigned int temp = setValues;
        //std::cout << "Size: " <<size() << '\n';

        if (temp & (1 << (value - 1))){
          return SudokuSquareSetIterator(value ,temp);
        }
        else{
          return end();
        }

    }

    SudokuSquareSetIterator begin() const{
      //std::cout << "Size: "<< size() << '\n';
      return SudokuSquareSetIterator(setValues).begin();
    }

    SudokuSquareSetIterator end() const{
      //std::cout << "Size: "<< size() << '\n';
      return SudokuSquareSetIterator(setValues).end();

    }

    // void printBinaryValue(unsigned int num)
    // {
    //   if(!num) return;
    //
    //   printBinaryValue(num>>1);
    //   putchar(((num&1 == 1) ? '1' : '0'));
    // }

    void erase(int value){
      // std::cout << "Value to erase: "<< value << '\n';
      // int bit = (setValues >> value - 1)  & 1U;
      // std::cout << "Bit before: "<< bit << '\n';
      // std::cout << "Binary before: " << '\n';
      // printBinaryValue(setValues);
      int bitPos = value - 1;

      setValues &= ~(1<<bitPos);

      // std::cout << "Check: " << '\n';
      // printBinaryValue(setValues);
      // std::cout <<  '\n';
      // std::cout << "Binary after: "<<  '\n';
      // printBinaryValue(temp);
      // bit = (setValues >> value - 1) & 1U;
      // std::cout << "Bit after: "<< bit << '\n';
      // std::cout << "Size after: " << size() << '\n';
    }

    void erase(SudokuSquareSetIterator& iter){

      int bitPos = *iter;

      setValues &= ~(1<<bitPos);

    }

    bool empty(){
      if (setValues == 0) {
        return true;
      }
      else{
        return false;
      }
    }

};


// Do not write any code below this line
static_assert(sizeof(SudokuSquareSet) == sizeof(unsigned int) + sizeof(int), "The SudokuSquareSet class needs to have exactly two 'int' member variables, and no others");


#endif
