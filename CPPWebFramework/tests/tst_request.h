#ifndef TST_HTTPSERVLETREQUEST_H
#define TST_HTTPSERVLETREQUEST_H

#include <QtTest>
#include <cwf/request.h>

class ClientTest : public QObject
{
    Q_OBJECT

    QString a;
    std::string b;
    bool c;
    char d;
    unsigned char e;
    short h;
    unsigned short i;
    int j;
    unsigned int k;
    long l;
    unsigned long m;
    long long n;
    unsigned long long o;
    float p;
    double q;
public slots:
    QString getA() const { return a; }

    void setA(const QString &value) { a = value; }

    std::string getB() const { return b; }

    void setB(const std::string &value) { b = value; }

    bool getC() const { return c; }

    void setC(bool value) { c = value; }

    char getD() const { return d; }

    void setD(char value) { d = value; }

    unsigned char getE() const { return e; }

    void setE(unsigned char value) { e = value; }

    short getH() const { return h; }

    void setH(short value) { h = value; }

    unsigned short getI() const { return i; }

    void setI(unsigned short value) { i = value; }

    int getJ() const { return j; }

    void setJ(int value) { j = value; }

    unsigned int getK() const { return k; }

    void setK(unsigned int value) { k = value; }

    long getL() const { return l; }

    void setL(long value) { l = value; }

    unsigned long getM() const { return m; }

    void setM(unsigned long value) { m = value; }

    long long getN() const { return n; }

    void setN(long long value) { n = value; }

    unsigned long long getO() const { return o; }

    void setO(unsigned long long value) { o = value; }

    float getP() const { return p; }

    void setP(float value) { p = value; }

    double getQ() const { return q; }

    void setQ(double value) { q = value; }
};


class TST_Request : public QObject
{
    Q_OBJECT
private slots:
    void test();
};

#endif // TST_HTTPSERVLETREQUEST_H
