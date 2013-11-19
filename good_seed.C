unsigned int good_seed()
{
    unsigned int random_seed, random_seed_a, random_seed_b; 
    std::ifstream file ("/dev/urandom", std::ios::binary);
    if (file.is_open())
    {
        char * memblock;
        int size = sizeof(int);
        memblock = new char [size];
        file.read (memblock, size);
        file.close();
        random_seed_a = *reinterpret_cast<int*>(memblock);
        delete[] memblock;
    }// end if
    else
    {
        random_seed_a = 0;
    }
    random_seed_b = std::time(0);
    random_seed = random_seed_a ^ random_seed_b;
    std::cout << "random_seed_a = " << random_seed_a << std::endl;
    std::cout << "random_seed_b = " << random_seed_b << std::endl;
    std::cout << " random_seed =  " << random_seed << std::endl;
    return random_seed;
} // end good_seed()
