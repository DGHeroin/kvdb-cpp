#include <iostream>
#include "kvdb.h"

using namespace std;

int main()
{
    KVDB db;
    // key 元组
    Variant key;
    key.add ("k1", 2);
    key.add ("k2", 2);

    // value 元组
    Variant value;
    int    i_val_1 = 100;
    double d_val_1 = 200.123;

    value.add ((char*)&i_val_1, sizeof(i_val_1));
    value.add ((char*)&d_val_1, sizeof(d_val_1));

    db.add (key, value);

    Variant v = db.get (key);

    cout << value.to_string () << endl;
    cout << v.to_string () << endl;

    int    i_val_2 = *(int*)v.get (0).c_str ();
    double d_val_2 = *(double*)v.get (1).c_str ();
    cout << "i_val_2:" << i_val_2 << " d_val_2:" << d_val_2 << endl;
    return 0;
}

