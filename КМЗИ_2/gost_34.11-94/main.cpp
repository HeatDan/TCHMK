#include "gost_r.h"

int main(int argc, char **argv)
 {
    if (argc != 2)
    {
        cout << endl << "ERROR usage: ./gost_r file_in" << endl << endl;

        return -1;
    }
    else
    {
        Gost_r hash;

        if (hash.read_file(argv[1]))
        {
            hash.gost_r();

            cout << "hash gost_r_34.11-94: "<<endl;
            hash.Show_hash();
        }
        else
            cout << "ERROR!!!FILE NOT FOUND!" << endl << endl;
    }

    return 0;
}
