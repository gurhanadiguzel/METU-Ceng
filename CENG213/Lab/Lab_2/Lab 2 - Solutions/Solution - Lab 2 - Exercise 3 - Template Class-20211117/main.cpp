#include "myvector.cpp"

int main(void)
{

    /*********************** INTEGER *************************/
    // Initialization Test
    std::cout << "-----------------------" << std::endl;
    std::cout << "INTEGER TESTING" << std::endl;
    std::cout << "Creating INT Vector" << std::endl;
    MyVector<int> myvector(DEFAULT_INIT_VAL_INT, DEFAULT_VEC_SIZE);
    std::cout << "INT Vector:\n" << myvector;

    // Size checking
    std::cout << "\nINT Vector Size: " << myvector.get_size() << std::endl;

    // Operator Overloading checking
    std::cout << "\nChanging 3th element from default to 5 (INT)" << std::endl;
    myvector[2] = 5;
    std::cout << "New INT Vector:\n" << myvector;

    // Changing Initial Value
    std::cout << "\nChanging initial value to 13. (INT)" << std::endl;
    myvector.set_init_val(13);

    // Resizing
    std::cout << "\nResizing INT Vector from default to 8: " << myvector.resize(8) << std::endl;
    std::cout << "New INT Vector:\n" << myvector;
    std::cout << "Resizing INT Vector from 8 to 2: " << myvector.resize(2) << std::endl;
    std::cout << "New INT Vector:\n" << myvector;

    // Appending
    std::cout << "\nAppending 213 to vector." << std::endl;
    myvector.append(213);
    std::cout << "INT Vector Size: " << myvector.get_size() << std::endl;
    std::cout << "New INT Vector:\n" << myvector;
    std::cout << "-----------------------" << std::endl;

    /********************************************************/



    /*********************** FLOAT **************************/
    std::cout << "FLOAT TESTING" << std::endl;
    std::cout << "Creating FLT Vector" << std::endl;
    MyVector<float> myvector_flt(DEFAULT_INIT_VAL_FLT, DEFAULT_VEC_SIZE);
    std::cout << "FLT Vector:\n" << myvector_flt;

    // Size checking
    std::cout << "\nFLT Vector Size: " << myvector_flt.get_size() << std::endl;

    // Operator Overloading checking
    std::cout << "\nChanging 3th element from default to 5.67 (FLT)" << std::endl;
    myvector_flt[2] = 5.67;
    std::cout << "New FLT Vector:\n" << myvector_flt;

    // Changing Initial Value
    std::cout << "\nChanging initial value to 13.33. (FLT)" << std::endl;
    myvector_flt.set_init_val(13.33);

    // Resizing
    std::cout << "\nResizing FLT Vector from default to 8: " << myvector_flt.resize(8) << std::endl;
    std::cout << "New FLT Vector:\n" << myvector_flt;
    std::cout << "Resizing FLT Vector from 8 to 2: " << myvector_flt.resize(2) << std::endl;
    std::cout << "New FLT Vector:\n" << myvector_flt;

    // Appending
    std::cout << "\nAppending 213.22 to vector." << std::endl;
    myvector_flt.append(213.22);
    std::cout << "FLT Vector Size: " << myvector_flt.get_size() << std::endl;
    std::cout << "New FLT Vector:\n" << myvector_flt;
    std::cout << "-----------------------" << std::endl;

    /********************************************************/



    /*********************** STRING **************************/
    std::cout << "STRING TESTING" << std::endl;
    std::cout << "Creating STR Vector" << std::endl;
    MyVector<std::string> myvector_str(DEFAULT_INIT_VAL_STR, DEFAULT_VEC_SIZE);
    std::cout << "STR Vector:\n" << myvector_str;

    // Size checking
    std::cout << "\nSTR Vector Size: " << myvector_str.get_size() << std::endl;

    // Operator Overloading checking
    std::cout << "\nChanging 3th element from default to 'FAIL' (STR)" << std::endl;
    myvector_str[2] = "FAIL";
    std::cout << "New STR Vector:\n" << myvector_str;

    // Changing Initial Value
    std::cout << "\nChanging initial value to 'CENG213'. (STR)" << std::endl;
    myvector_str.set_init_val("CENG213");

    // Resizing
    std::cout << "\nResizing STR Vector from default to 8: " << myvector_str.resize(8) << std::endl;
    std::cout << "New STR Vector:\n" << myvector_str;
    std::cout << "Resizing STR Vector from 8 to 2: " << myvector_str.resize(2) << std::endl;
    std::cout << "New STR Vector:\n" << myvector_str;
    
    // Appending
    std::cout << "\nAppending 'FINE' to vector." << std::endl;
    myvector_str.append("FINE");
    std::cout << "STR Vector Size: " << myvector_str.get_size() << std::endl;
    std::cout << "New STR Vector:\n" << myvector_str;
    std::cout << "-----------------------" << std::endl;

    return 0;
}
