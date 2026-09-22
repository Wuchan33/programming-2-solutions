// Mikolaj Suchan

int to_int(char* curr) {
    int ans = 0;
    ans += (*curr - '0') * 16;
    curr++;
    ans += (*curr - '0') * 8;
    curr++;
    ans += (*curr - '0') * 4;
    curr++;
    ans += (*curr - '0') * 2;
    curr++;
    ans += (*curr - '0') * 1;
    return ans;
}

void add(char* curr, int* set) {
    int val = to_int(curr);
    *set |= (1 << val);
}

void Insert(char* curr, int* set) {
    if (*curr == 0)
        return;
    if (*curr == ' ')
        Insert(curr + 1, set);
    else {
        add(curr, set);
        Insert(curr + 5, set);
    }
}

void Emplace(char* curr, int* set) {
    *set = 0;
    Insert(curr, set);
}

void Erase(char* curr, int* set) {
    if (*curr == 0)
        return;
    if (*curr == ' ')
        Erase(curr + 1, set);
    else {
        int val = to_int(curr);
        if (*set & (1 << val))
            *set -= (1 << val);
        Erase(curr + 5, set);
    }
}

bool Emptiness(int set) {
    return set == 0;
}

bool Nonempty(int set) {
    return set != 0;
}

void Print(int set, char* curr) {
    if (set == 0) {
        *curr++ = 'e';
        *curr++ = 'm';
        *curr++ = 'p';
        *curr++ = 't';
        *curr++ = 'y';
        *curr = 0;
        return;
    }

    if (set & (1 << 31)) {
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 30)) {
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 29)) {
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 28)) {
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 27)) {
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 26)) {
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 25)) {
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 24)) {
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 23)) {
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 22)) {
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 21)) {
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 20)) {
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 19)) {
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 18)) {
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 17)) {
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 16)) {
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 15)) {
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 14)) {
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 13)) {
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 12)) {
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 11)) {
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 10)) {
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 9)) {
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 8)) {
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 7)) {
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 6)) {
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 5)) {
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 4)) {
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 3)) {
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 2)) {
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = '0';
        *curr++ = ' ';
    }

    if (set & (1 << 1)) {
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '1';
        *curr++ = ' ';
    }

    if (set & (1 << 0)) {
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = '0';
        *curr++ = ' ';
    }

    curr--;
    *curr = 0;
}

bool Member(char* curr, int set) {
    if (*curr == ' ')
        return Member(curr + 1, set);
    int val = to_int(curr);
    return (set & (1 << val)) != 0;
}

bool Disjoint(int A, int B) {
    return (A & B) == 0;
}

bool Conjunctive(int A, int B) {
    return (A & B) != 0;
}

bool Equality(int A, int B) {
    return (A ^ B) == 0;
}

bool Inclusion(int A, int B) {
    return (A & B) == A;
}

void Union(int A, int B, int* set) {
    *set = (A | B);
}

void Intersection(int A, int B, int* set) {
    *set = (A & B);
}

void Symmetric(int A, int B, int* set) {
    *set = (A ^ B);
}

void Difference(int A, int B, int* set) {
    *set = (A ^ (A & B));
}

void Complement(int A, int* set) {
    *set = (~A);
}

int Cardinality(int set) {
    if (set == 0)
        return 0;
    return (set < 0) + Cardinality(set << 1);
}

bool LessThan(int A, int B) {
    int A_cnt = Cardinality(A), B_cnt = Cardinality(B);
    if (A_cnt < B_cnt)
        return true;
    else if (A_cnt > B_cnt)
        return false;
    int A_bit = (A & (1 << 31)), B_bit = (B & (1 << 31));
    if (B_bit && !A_bit)
        return true;
    if (A_bit && !B_bit)
        return false;
    if (A_bit && B_bit) {
        A ^= (1 << 31);
        B ^= (1 << 31);
    }
    return A < B;
}

bool LessEqual(int A, int B) {
    int A_cnt = Cardinality(A), B_cnt = Cardinality(B);
    if (A_cnt < B_cnt)
        return true;
    else if (A_cnt > B_cnt)
        return false;
    int A_bit = (A & (1 << 31)), B_bit = (B & (1 << 31));
    if (B_bit && !A_bit)
        return true;
    if (A_bit && !B_bit)
        return false;
    if (A_bit && B_bit) {
        A ^= (1 << 31);
        B ^= (1 << 31);
    }
    return A <= B;
}

bool GreatEqual(int A, int B) {
    int A_cnt = Cardinality(A), B_cnt = Cardinality(B);
    if (A_cnt > B_cnt)
        return true;
    else if (A_cnt < B_cnt)
        return false;
    int A_bit = (A & (1 << 31)), B_bit = (B & (1 << 31));
    if (B_bit && !A_bit)
        return false;
    if (A_bit && !B_bit)
        return true;
    if (A_bit && B_bit) {
        A ^= (1 << 31);
        B ^= (1 << 31);
    }
    return A >= B;
}

bool GreatThan(int A, int B) {
    int A_cnt = Cardinality(A), B_cnt = Cardinality(B);
    if (A_cnt > B_cnt)
        return true;
    else if (A_cnt < B_cnt)
        return false;
    int A_bit = (A & (1 << 31)), B_bit = (B & (1 << 31));
    if (B_bit && !A_bit)
        return false;
    if (A_bit && !B_bit)
        return true;
    if (A_bit && B_bit) {
        A ^= (1 << 31);
        B ^= (1 << 31);
    }
    return A > B;
}
