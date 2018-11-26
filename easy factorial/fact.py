t = input()
while( t > 0 ):
    u = input()
    fact = 1
    while( u > 0 ):
        fact = fact * u
        u = u - 1
    t = t - 1
    print fact

