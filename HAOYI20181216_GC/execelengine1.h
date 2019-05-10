#ifndef EXECELENGINE1_H
#define EXECELENGINE1_H

#ifndef EXCELENGINE_H
#define EXCELENGINE_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QAxBase>
#include <QAxObject>

#include <QTableWidget>
#include <QTableView>
#include <QTableWidgetItem>
#include <QDebug>

typedef unsigned int UINT;

/*
     ExcelEngine excel; //??excel??
     excel.Open(QObject::tr("c:\\Test.xls"),1,false); //?????xls?????sheet????????

     int num = 0;
     for (int i=1; i<=10; i++)
     {
         for (int j=1; j<=10; j++)
         {
            excel.SetCellData(i,j,++num); //????????
         }
     }

     QVariant data = excel.GetCellData(1,1); //?????????
     excel.GetCellData(2,2);
     excel.GetCellData(3,3);
     excel.Save(); //??
     excel.Close();
*/

//?????tablewidget?
/*
    ExcelEngine excel(QObject::tr("c:\\Import.xls"));
    excel.Open();
    excel.ReadDataToTable(ui->tableWidget); //???widget?
    excel.Close();
*/

//?tablewidget???????excel?
/*
    ExcelEngine excel(QObject::tr("c:\\Export.xls"));
    excel.Open();
    excel.SaveDataFrTable(ui->tableWidget); //????
    excel.Close();
*/
/**
  *@brief ีโสวาปธ๖ฑใำฺQtถมะดexcelทโืฐตฤภเฃฌอฌสฑฃฌฑใำฺฐัexcelึะตฤสพ
  *ฯิสพตฝฝ็รๆษฯฃฌป๒ี฿ฐัฝ็รๆษฯตฤสพะดศ๋excelึะฃฌอฌGUIฝ๘ะะฝปปฅฃฌนุฯตศ็ฯยฃบ
  *Qt tableWidget <--> ExcelEngine <--> xls file.
  *
  *@note ExcelEngineภเึปธบิ๐ถม/ะดสพฃฌฒปธบิ๐ฝโฮ๖ฃฌื๖ึะผไฒใ
  *@author yaoboyuan 254200341@qq.com
  *@date 2012-4-12
  */
class ExcelEngine : protected QObject
{
public:
    ExcelEngine();
    ExcelEngine(QString xlsFile);
    ~ExcelEngine();

public:
    bool Open(UINT nSheet = 1, bool visible = false);//ด๒ฟชxlsฮฤผ
    bool Open(QString xlsFile, UINT nSheet = 1, bool visible = false);
    void Save();                //ฑฃดๆxlsฑจฑํ
    void Close();               //นุฑีxlsฑจฑํ

    bool SaveDataFrTable(QTableWidget *tableWidget); //ฑฃดๆสพตฝxls
    bool ReadDataToTable(QTableWidget *tableWidget); //ดำxlsถมศกสพตฝui

    QVariant GetCellData(UINT row, UINT column);                //ป๑ศกึธถจตฅิชสพ
    bool     SetCellData(UINT row, UINT column, QVariant data); //ะธฤึธถจตฅิชสพ

    UINT GetRowCount()const;
    UINT GetColumnCount()const;

    bool IsOpen();
    bool IsValid();

protected:
    void Clear();

private:
    QAxObject *pExcel;      //ึธฯ๒ี๛ธ๖excelำฆำรณฬะ๒
    QAxObject *pWorkbooks;  //ึธฯ๒นคื๗ฒพผฏ,excelำะบถเนคื๗ฒพ
    QAxObject *pWorkbook;   //ึธฯ๒sXlsFileถิำฆตฤนคื๗ฒพ
    QAxObject *pWorksheet;  //ึธฯ๒นคื๗ฒพึะตฤฤณธ๖sheetฑํตฅ

    QString   sXlsFile;     //xlsฮฤผยทพถ
    UINT      nCurrSheet;   //ตฑวฐด๒ฟชตฤตฺผธธ๖sheet
    bool      bIsVisible;   //excelสวท๑ฟษผ๛
    int       nRowCount;    //ะะส
    int       nColumnCount; //มะส
    int       nStartRow;    //ฟชสผำะสพตฤะะฯยฑ๊ึต
    int       nStartColumn; //ฟชสผำะสพตฤมะฯยฑ๊ึต

    bool      bIsOpen;      //สวท๑าัด๒ฟช
    bool      bIsValid;     //สวท๑ำะะง
    bool      bIsANewFile;  //สวท๑สวาปธ๖ะยฝจxlsฮฤผฃฌำรภดว๘ทึด๒ฟชตฤexcelสวาัดๆิฺฮฤผปนสวำะฑพภเะยฝจตฤ
    bool      bIsSaveAlready;//ทภึนึุธดฑฃดๆ

};

#endif // EXCELENGINE_H


#endif // EXECELENGINE1_H

