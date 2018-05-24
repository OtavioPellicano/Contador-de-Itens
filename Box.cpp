#include "Box.h"
#include <QDebug>

Box::Box()
{
    setFiltro(QStringList("*.csv"));
    setSep(";");
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

QString Box::strArqSaida() const
{
    return mStrArqSaida;
}

void Box::setStrArqSaida(const QString &strArqSaida)
{
    mStrArqSaida = strArqSaida;
}

unsigned short Box::colBusca() const
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

//    if(!this->dirOut().exists() || this->dirOut().path() == ".")
//        return false;

//    if(this->strArqSaida().isEmpty())
//        return false;

    if(this->fullPathArqOut().isEmpty())
        return false;

    QStringList arqs = this->dirIn().entryList(this->filtro());
    ifstream arqIn;
    map<QString, size_t> mapItens;
    string str;
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
                try {
                    mapItens[strCsv[colBusca()]] += 1;
                } catch (...) {
                    qDebug() << "File to big to be processed!";
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


    if(!this->fullPathArqOut().isEmpty())
    {
        arqOut.open(this->fullPathArqOut().toStdString());
    }
    else
    {
        arqOut.open(this->dirOut().absoluteFilePath(this->strArqSaida()).toStdString());
    }



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
        qDebug() << "failed to open: " << this->strArqSaida();
        return false;
    }

    mapItens.clear();
    return true;
}

QString Box::fullPathArqOut() const
{
    return mFullPathArqOut;
}

void Box::setFullPathArqOut(const QString &fullPathArqOut)
{
    mFullPathArqOut = fullPathArqOut;
}
