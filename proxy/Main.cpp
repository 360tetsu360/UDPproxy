#include <stdio.h>
#include <iostream>
#include "Proxy.h"


int main() {
    Proxy p = Proxy();
    p.Initialize(19131, "127.0.0.1", 19132);
    p.Start();
    return 0;
}