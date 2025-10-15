import random

# Brute force calculation for running tests
def brute_force(deliveries1, deliveries2, charge1, charge2, hour=1):
    if deliveries1 == 0 and deliveries2 == 0:
        return hour - 1

    elif hour % charge1 == 0 and hour % charge2 == 0:
        return brute_force(deliveries1, deliveries2, charge1, charge2, hour=hour + 1)

    elif hour % charge1 == 0:
        if deliveries2 > 0:     return brute_force(deliveries1, deliveries2 - 1, charge1, charge2, hour=hour + 1)
        else:                   return brute_force(deliveries1, deliveries2, charge1, charge2, hour=hour + 1)

    elif hour % charge2 == 0:
        if deliveries1 > 0:     return brute_force(deliveries1 - 1, deliveries2, charge1, charge2, hour=hour + 1)
        else:                   return brute_force(deliveries1, deliveries2, charge1, charge2, hour=hour + 1)

    else:
        if deliveries1 == 0:    return brute_force(deliveries1, deliveries2 - 1, charge1, charge2, hour=hour + 1)
        elif deliveries2 == 0:  return brute_force(deliveries1 - 1, deliveries2, charge1, charge2, hour=hour + 1)
        else:
            return min(
                brute_force(deliveries1 - 1, deliveries2, charge1, charge2, hour=hour + 1),
                brute_force(deliveries1, deliveries2 - 1, charge1, charge2, hour=hour + 1))

def euclidean_algorithm(n1, n2):
    while n1 > 0 and n2 > 0:
        if n1 > n2:
            n1 = n1 % n2
        elif n2 > n1:
            n2 = n2 % n1
        else:
            return n1

    return max(n1, n2)

def smart(deliveries1, deliveries2, charge1, charge2):
    charge_time1 = deliveries1 // (charge1 - 1) - int(deliveries1 % (charge1 - 1) == 0)
    charge_time2 = deliveries2 // (charge2 - 1) - int(deliveries2 % (charge2 - 1) == 0)

    gcd = euclidean_algorithm(charge1, charge2)
    lcm = charge1 * charge2 // gcd if gcd > 0 else deliveries1 * deliveries2
    
    if charge_time1 - ((deliveries1 + charge_time1) // lcm - int((deliveries1 + charge_time1) % lcm == 0)) > deliveries2: return deliveries1 + charge_time1
    if charge_time2 - ((deliveries2 + charge_time2) // lcm - int((deliveries2 + charge_time2) % lcm == 0)) > deliveries1: return deliveries2 + charge_time2

    total_deliveries = deliveries1 + deliveries2

    return total_deliveries + (total_deliveries // (lcm - 1) - int(total_deliveries % (lcm - 1) == 0))

def run_test():
    num_tests = 10000
    for _ in range(num_tests):
        d1, d2 = random.randint(1, 10), random.randint(1, 10)
        c1, c2 = random.randint(2, 30), random.randint(2, 30)

        smart_result = smart(d1, d2, c1, c2)
        brute_result = brute_force(d1, d2, c1, c2)
        if smart_result != brute_result:
            print(f"❌ Error for input {d1}, {d2}, {c1}, {c2}:\n\tBrute: {brute_result}\n\tSmart: {smart_result}")
            return

    print("✅ All tests passed!")


run_test()
