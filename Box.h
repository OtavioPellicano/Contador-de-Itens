#ifndef BOX_H
#define BOX_H

#include <QDir>
#include <QStringList>
#include <fstream>
#include <map>

using std::map;
using std::ifstream;
using std::ofstream;
using std::string;

class Box
{
public:
    Box();

    QDir dirIn() const;
    void setDirIn(const QDir &dirIn);

    QDir dirOut() const;
    void setDirOut(const QDir &dirOut);

    QString strArqSaida() const;
    void setStrArqSaida(const QString &strArqSaida);

    unsigned short colBusca() const;
    void setColBusca(unsigned short colBusca);

    bool processar();

    QStringList filtro() const;
    void setFiltro(const QStringList &filtro);

    QString sep() const;
    void setSep(const QString &sep);

    QString fullPathArqOut() const;
    void setFullPathArqOut(const QString &fullPathArqOut);

private:
    bool descarregarMap(map<QString, size_t> &mapItens);

private:

    QDir mDirIn;
    QDir mDirOut;
    QString mStrArqSaida;
    QString mSep;
    QString mFullPathArqOut;
    unsigned short mColBusca;
    QStringList mFiltro;

};

#endif // BOX_H
