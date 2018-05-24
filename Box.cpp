#include "Box.h"
#include <QDebug>

Box::Box()
{
    setFiltro(QStringList("*.csv"));
    setSep(";");
    setColBusca2(-1);
}

QDir Box::dirIn() const
{
    return mDirIn;
}

void Box::setDirIn(const QDir &dirIn)
{
    mDirIn = dirIn;
}

QDir Box::dirOut() const
{
    return mDirOut;
}

void Box::setDirOut(const QDir &dirOut)
{
    mDirOut = dirOut;
}

short Box::colBusca() const
{
    return mColBusca;
}

void Box::setColBusca(unsigned short colBusca)
{
    mColBusca = colBusca;
}

bool Box::processar()
{
    if(!this->dirIn().exists() || this->dirIn().path() == ".")
        return false;

    if(this->fullPathArqOut().isEmpty())
        return false;

    QStringList arqs = this->dirIn().entryList(this->filtro());
    ifstream arqIn;
    map<QString, size_t> mapItens;
    string str;
    QString chave;
    QStringList strCsv;

    if(arqs.isEmpty())
        return false;

    for(QStringList::iterator itQStr = arqs.begin(); itQStr != arqs.end(); ++itQStr)
    {
        arqIn.open(this->dirIn().absoluteFilePath(*itQStr).toStdString());

        if(arqIn.is_open())
        {
            while(std::getline(arqIn, str))
            {
                strCsv = QString::fromStdString(str).split(this->mSep);

                if(colBusca() >= strCsv.size())
                    return false;

                if(colBusca2() >= strCsv.size())
                    return false;

                if(colBusca2() >= 0)
                    chave = strCsv[colBusca()] % "\t" % strCsv[colBusca2()];
                else
                    chave = strCsv[colBusca()];

                try {
                    mapItens[chave] += 1;
                } catch (...) {
                    qDebug() << "File too big to be processed!";
                    return false;
                }
            }
            arqIn.close();
        }
        else
        {
            qDebug() << "Failed to open:" << *itQStr;
        }
    }

    if(!descarregarMap(mapItens))
        return false;


    return true;
}

QStringList Box::filtro() const
{
    return mFiltro;
}

void Box::setFiltro(const QStringList &filtro)
{
    mFiltro = filtro;
}

QString Box::sep() const
{
    return mSep;
}

void Box::setSep(const QString &sep)
{
    mSep = sep;
}

bool Box::descarregarMap(map<QString, size_t> &mapItens)
{
    ofstream arqOut;

    arqOut.open(this->fullPathArqOut().toStdString());

    if(arqOut.is_open())
    {
        arqOut << "item" << this->sep().toStdString() << "qnt" << std::endl;

        for(map<QString, size_t>::iterator itMap = mapItens.begin(); itMap != mapItens.end(); ++itMap)
        {
            arqOut << (itMap->first).toStdString() << this->sep().toStdString() << std::to_string(itMap->second) << std::endl;
        }
        arqOut.close();
    }
    else
    {
        qDebug() << "failed to open: " << this->fullPathArqOut();
        return false;
    }

    mapItens.clear();
    return true;
}

short Box::colBusca2() const
{
    return mColBusca2;
}

void Box::setColBusca2(short colBusca2)
{
    mColBusca2 = colBusca2;
}

QString Box::fullPathArqOut() const
{
    return mFullPathArqOut;
}

void Box::setFullPathArqOut(const QString &fullPathArqOut)
{
    mFullPathArqOut = fullPathArqOut;
}
