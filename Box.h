#ifndef BOX_H
#define BOX_H

#include <QDir>
#include <QStringList>
#include <fstream>
#include <map>
#include <QStringBuilder>

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

    short colBusca() const;
    void setColBusca(unsigned short colBusca);

    bool processar();

    QStringList filtro() const;
    void setFiltro(const QStringList &filtro);

    QString sep() const;
    void setSep(const QString &sep);

    QString fullPathArqOut() const;
    void setFullPathArqOut(const QString &fullPathArqOut);

    short colBusca2() const;
    void setColBusca2(short colBusca2);

    QString msgLog() const;
    void setMsgLog(const QString &msgLog);


private:
    bool descarregarMap(map<QString, size_t> &mapItens);
    unsigned long qntLinhas() const;
    void setQntLinhas(unsigned long qntLinhas);


private:

    QDir mDirIn;
    QDir mDirOut;
    QString mSep;
    QString mFullPathArqOut;
    short mColBusca;
    short mColBusca2;
    QStringList mFiltro;
    QString mMsgLog;

    unsigned long mQntLinhas;

};

#endif // BOX_H
