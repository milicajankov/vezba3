#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>

using namespace std;

class Proizvod {
    int id;
    char oznaka;
public:
    Proizvod(int i, char oz): id(i), oznaka(oz) { }

    virtual double zapremina()const=0;

    virtual string ispis()const{
        return string("( ") + to_string(id) + " )" ;
    }
    virtual bool poredjenje(const Proizvod &p)const{
        return (oznaka==p.oznaka);
    }
    friend bool operator==(const Proizvod &p1, const Proizvod &p2){
        return p1.poredjenje(p2);
    }
    friend bool operator != (const Proizvod &p1, const Proizvod &p2){
        return !(p1.poredjenje(p2));
    }
    friend ostream& operator << (ostream &out, const Proizvod &p){
        out << p.ispis() << endl;
        return out ;

    }
//*/
};
class Sanduk : public Proizvod{
    double a, b, c;
public:
    Sanduk(int i=0, double aa=0., double bb=0., double cc=0.): Proizvod(i,'S'), a(aa), b(bb), c(cc) { }

    bool poredjenje(const Sanduk &s)const{
        return Proizvod::poredjenje(s) && (a==s.a) && (b==s.b) && (c==s.c);
    }
    string ispis()const{
       return  Proizvod::ispis() + 'S' + " " + "(" + to_string(a) + ", " + to_string(b) + ", " + to_string(c) + ")";
    }
    double zapremina()const{
        return a*b*c;
    }
};
class Bure : public Proizvod {
    double r, h;
public:
    Bure(int i=0, double rr=0., double hh=0.): Proizvod(i, 'B'), r(rr), h(hh) { }

    string ispis()const{
        return Proizvod::ispis() + 'B' + " " + "(" + to_string(r) + "," + to_string(h) + ")";
    }
    bool poredjenje(const Bure &b)const{
        return Proizvod::poredjenje(b) && (r==b.r) && (h==b.h);
    }
    double zapremina()const{
        return 2*r*h*M_PI;
    }

};
class Skladiste{
    vector<Proizvod*> niz;
    int max_mesta;
    double max_zapremina;

public:
    Skladiste(int m, int z): max_mesta(m), max_zapremina(z) { }

    int trenutni_broj()const{
        return niz.size();
    }

    int maks_broj()const{
        return max_mesta;
    }

    double ukupna_zap()const{
        double res=0.;
        for(auto x: niz)
            res+=x->zapremina();
            return res;
    }

    double raspoloziva_zap()const{
        return max_zapremina - ukupna_zap();
    }


    void unos(Proizvod *p){
        if((trenutni_broj()< max_mesta) && (ukupna_zap()<max_zapremina))
            niz.push_back(p);
        return;
    }
    void izbaci(const Proizvod *p){
        size_t i = 0;
        for(i=0; i<niz.size(); ++i)
            if(*niz[i] == *p){
            niz.erase(niz.begin() + i);
            }

    }

    friend ostream& operator << (ostream &out, const Skladiste &s){

    out << "Sadrzaj skladista: " << endl;
    for(auto p: s.niz)
        out << (*p) << endl;
        return out;
    }
};
int main()
{
    Skladiste s(340, 570);
    s.unos(new Sanduk(1, 3., 5. ,6.));
    s.unos(new Sanduk(2, 3., 5., 7.));
    s.unos(new Bure(1, 3, 5));
    s.unos(new Bure(2, 45, 6));
    cout << s << endl;

    s.izbaci(new Bure(2, 45, 6));
    s.izbaci(new Bure(1, 3, 5));
    cout << s << endl;

    cout << s.trenutni_broj() << endl;
    cout << s.raspoloziva_zap() << endl;
    cout << s.ukupna_zap() << endl;
    cout << s.maks_broj() << endl;

    return 0;
}
