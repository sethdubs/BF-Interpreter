#include "bf.h"

#include <algorithm>
#include <algorithm>
#include <array>
#include <iostream>
#include <string>


BF::BF()
{
  reset();
}

void BF::reset()
{
  std::fill(mem_, mem_ + MEM_SIZE, 0);
  ptr_ = 0;
}


bool BF::interpret(const std::string &src, bytestream &is, bytestream &os)
{

    int offset = 0;
    int bracketCount = 0;
    bool checked = false;
    int c = 0;
    int b = 0;
    int p = 0;
    int l1 = 0;
    int b1 = 0;
    int l2 = 0;
    int b2 = 0;
    
    
    while (src[b]){

        switch(src[b]){ // Switch to handle each of the characters in the language
                
                
            case '+': // Increment value in array
                
                mem_[ptr_]++;
                break;
                
            case '-': // Decrement value in array
                mem_[ptr_]--;
                break;
                
            case '>': // Increment place in array
                if(ptr_ == MEM_SIZE)
                {
                    ptr_ = 0; // If at end of array on increment; set place to start
                }
                else
                {
                    ptr_++;
                }
                break;
                
            case '<': // Decrement place in array
                if(ptr_ == 0)
                {
                    ptr_ = MEM_SIZE; // If at start of array on decrement; set place to end
                }
                else
                {
                    ptr_--;
                }
                break;
 
            case '[': //start loop
                
                if(!checked)
                {
                    c = b;
                    while(src[b]) // checking that the loop open has a loop close to be paired with
                    {
                        if(src[b] == '[') bracketCount++;
                        if(src[b] == ']' && bracketCount != 0)
                        {
                            bracketCount--;
                        }
                        b++;
                    }
                    if(bracketCount != 0)
                    {
                        std::cout << "WARNING: unbalanced loop indicators. Every open bracket '[' must be closed ']'" << std:: endl;
                        return false;
                    }
                    checked = true;
                    b = c;
                }
                
                if (offset == 0 && b1 == 0)
                {
                    offset = 1;
                    b1 = b;
                    l1 = ptr_;
                }
                else if (offset == 1 && b2 == 0)
                {
                    offset = 2;
                    b2 = b;
                    l2 = ptr_;
                }
                
                break;
                
                
                
                
            case ']': // close loop
                
                if(!checked) {
                    std::cout << "WARNING: Cannot use the close loop indicator ']' prior to opening the loop '['" << std:: endl;
                    return false;
                }
                if(offset == 1 && mem_[l1] != 0)
                {
                    b = b1;
                }
                else if(offset == 1 && mem_[l1] == 0)
                {
                    l1 = 0;
                    offset = 0;
                    b1 = 0;
                }
                if(offset == 2 && mem_[l2] != 0)
                {
                    
                    b = b2;
                }
                else if(offset == 2 && mem_[l2] == 0)
                {
                    offset = 1;
                    l2 = 0;
                    b2 = 0;
                }
                break;
                
                
                
                
            case '.': // Output to stdout
                os.write(mem_ + ptr_, 1);
                break;
                
                
                
                
            case ',': // Input ascii value stdin
                os.read(mem_ + ptr_, 1);
                break;
                
                
        }
        b++;
    }

  return true;
}
