#ifndef OPTIONSMODEL_H
#define OPTIONSMODEL_H

#include <QAbstractListModel>

/** Interface from Qt to configuration data structure for Bitcoin client.
   To Qt, the options are presented as a list with the different options
   laid out vertically.
   This can be changed to a tree once the settings become sufficiently
   complex.
 */
class OptionsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit OptionsModel(QObject *parent = 0);

    enum OptionID {
        StartAtStartup,         // bool
        MinimizeToTray,         // bool
        MapPortUPnP,            // bool
        MinimizeOnClose,        // bool
        ProxyUse,               // bool
        ProxyIP,                // QString
        ProxyPort,              // int
        ProxySocksVersion,      // int
        FeeUnxCoin,             // qint64
        ReserveBalanceUnxCoin,  // qint64
        DefaultColor,           // int
        DisplayUnitUnxCoin,     // BitcoinUnits::Unit
        DisplayAddresses,       // bool
        DetachDatabases,        // bool
        Language,               // QString
        CoinControlFeatures,    // bool
        OptionIDRowCount,
    };

    void Init();

    /* Migrate settings from wallet.dat after app initialization */
    bool Upgrade(); /* returns true if settings upgraded */

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    /* Explicit getters */
    qint64 getTransactionFeeUnxCoin();
    qint64 getReserveBalanceUnxCoin();
    bool getMinimizeToTray();
    bool getMinimizeOnClose();
    int getDefaultColor();
    int getDisplayUnit(int nColor);
    int getDisplayUnitUnxCoin();
    bool getDisplayAddresses();
    bool getCoinControlFeatures();
    QString getLanguage() { return language; }

private:
    int nDisplayUnitUnxCoin;
    bool bDisplayAddresses;
    bool fMinimizeToTray;
    bool fMinimizeOnClose;
    bool fCoinControlFeatures;
    QString language;

signals:
    void defaultColorChanged(int);
    void displayUnitChangedUnxCoin(int);
    void transactionFeeChangedUnxCoin(qint64);
    void reserveBalanceChangedUnxCoin(qint64);
    void coinControlFeaturesChanged(bool);
};

#endif // OPTIONSMODEL_H
