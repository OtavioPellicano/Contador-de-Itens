#include "Box.h"
#include <QDebug>

Box::Box()
{
    setFiltro(QStringList("*.csv"));
    setSep(";");
    setColBusca2(-1);
    setQntLinhas(0);
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
    {
        setMsgLog("Diretório de origem não válido!");
        return false;
    }

    if(this->fullPathArqOut().isEmpty())
    {
        setMsgLog("Selecione um local para salvar o arquivo!");
        return false;
    }

    QStringList arqs = this->dirIn().entryList(this->filtro());
    ifstream arqIn;
    map<QString, size_t> mapItens;
    string str;
    QString chave;
    QStringList strCsv;

    if(arqs.isEmpty())
    {
        setMsgLog("Não existem arquivos no diretório selecionado com o formato:\n" % filtro()[0]);
        return false;
    }

    for(QStringList::iterator itQStr = arqs.begin(); itQStr != arqs.end(); ++itQStr)
    {
        arqIn.open(this->dirIn().absoluteFilePath(*itQStr).toStdString());

        if(arqIn.is_open())
        {
            while(std::getline(arqIn, str))
            {
                strCsv = QString::fromStdString(str).split(this->mSep);

                if(colBusca() >= strCsv.size() || colBusca2() >= strCsv.size())
                {
                    setMsgLog("\"Coluna de Busca\" não encontrada!\nVocê está usando o separador correto?");
                    return false;
                }

                if(colBusca2() >= 0)
                    chave = strCsv[colBusca()] % "\t" % strCsv[colBusca2()];
                else
                    chave = strCsv[colBusca()];

                try {
                    mapItens[chave] += 1;
                } catch (...) {
                    setMsgLog("Número de dados superior ao que a aplicação pode tratar!");
                    qDebug() << "File too big to be processed!";
                    return false;
                }

                ++this->mQntLinhas;
            }
            arqIn.close();
        }
        else
        {
            setMsgLog("Impossivel abrir o arquivo:\n" % *itQStr);
            return false;
            qDebug() << "Failed to open:" << *itQStr;
        }
    }

    if(!descarregarMap(mapItens))
    {
        setMsgLog("Impossivel salvar o arquivo:\n" % fullPathArqOut());
        return false;
    }


    setMsgLog("Linhas processadas:\n" % QString::number(qntLinhas()));
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

unsigned long Box::qntLinhas() const
{
    return mQntLinhas;
}

void Box::setQntLinhas(unsigned long qntLinhas)
{
    mQntLinhas = qntLinhas;
}

QString Box::msgLog() const
{
    return mMsgLog;
}

void Box::setMsgLog(const QString &msgErro)
{
    mMsgLog = msgErro;
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
