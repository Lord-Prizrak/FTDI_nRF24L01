#include "ftdipinout.h"
#include <QDebug>


FTDIPinout::FTDIPinout(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    pins  << ui.comboBox_CE << ui.comboBox_SCK << ui.comboBox_MOSI << ui.comboBox_MISO << ui.comboBox_CSN ;
    resets << ui.toolButton_CE << ui.toolButton_SCK << ui.toolButton_MOSI << ui.toolButton_MISO << ui.toolButton_CSN;

    FT232RL_pinName.insert(1, "TXD");
    FT232RL_pinName.insert(2, "DTR#");
    FT232RL_pinName.insert(3, "RTS#");
    FT232RL_pinName.insert(4, "VCCIO");
    FT232RL_pinName.insert(5, "RXD");
    FT232RL_pinName.insert(6, "RI#");
    FT232RL_pinName.insert(7, "GND");
    FT232RL_pinName.insert(8, "NC");
    FT232RL_pinName.insert(9, "DSR#");
    FT232RL_pinName.insert(10, "DCD#");
    FT232RL_pinName.insert(11, "CTS#");
    FT232RL_pinName.insert(12, "CBUS4");
    FT232RL_pinName.insert(13, "CBUS2");
    FT232RL_pinName.insert(14, "CBUS3");
    FT232RL_pinName.insert(15, "USBDP");
    FT232RL_pinName.insert(16, "USBDM");
    FT232RL_pinName.insert(17, "3V3OUT");
    FT232RL_pinName.insert(18, "GND");
    FT232RL_pinName.insert(19, "RESET#");
    FT232RL_pinName.insert(20, "VCC");
    FT232RL_pinName.insert(21, "GND");
    FT232RL_pinName.insert(22, "CBUS1");
    FT232RL_pinName.insert(23, "CBUS0");
    FT232RL_pinName.insert(24, "NC");
    FT232RL_pinName.insert(25, "AGND");
    FT232RL_pinName.insert(26, "TEST");
    FT232RL_pinName.insert(27, "OSCI");
    FT232RL_pinName.insert(28, "OSCO");

    FT232RL_mapping.insert(0, 1);
    FT232RL_mapping.insert(1, 5);
    FT232RL_mapping.insert(2, 3);
    FT232RL_mapping.insert(3, 11);
    FT232RL_mapping.insert(4, 2);
    FT232RL_mapping.insert(5, 9);
    FT232RL_mapping.insert(6, 10);
    FT232RL_mapping.insert(7, 6);

    FT232RQ_pinName.insert(1, "VCCIO");
    FT232RQ_pinName.insert(2, "RXD");
    FT232RQ_pinName.insert(3, "RI#");
    FT232RQ_pinName.insert(4, "GND");
    FT232RQ_pinName.insert(5, "NC");
    FT232RQ_pinName.insert(6, "DSR#");
    FT232RQ_pinName.insert(7, "DCD#");
    FT232RQ_pinName.insert(8, "CTS#");
    FT232RQ_pinName.insert(9, "CBUS4");
    FT232RQ_pinName.insert(10, "CBUS2");
    FT232RQ_pinName.insert(11, "CBUS3");
    FT232RQ_pinName.insert(12, "NC");
    FT232RQ_pinName.insert(13, "NC");
    FT232RQ_pinName.insert(14, "USBDP");
    FT232RQ_pinName.insert(15, "USBDM");
    FT232RQ_pinName.insert(16, "3V3OUT");
    FT232RQ_pinName.insert(17, "GND");
    FT232RQ_pinName.insert(18, "RESET#");
    FT232RQ_pinName.insert(19, "VCC");
    FT232RQ_pinName.insert(20, "GND");
    FT232RQ_pinName.insert(21, "CBUS1");
    FT232RQ_pinName.insert(22, "CBUS0");
    FT232RQ_pinName.insert(23, "NC");
    FT232RQ_pinName.insert(24, "AGND");
    FT232RQ_pinName.insert(25, "NC");
    FT232RQ_pinName.insert(26, "TEST");
    FT232RQ_pinName.insert(27, "OSCI");
    FT232RQ_pinName.insert(28, "OSCO");
    FT232RQ_pinName.insert(29, "NC");
    FT232RQ_pinName.insert(30, "TXD");
    FT232RQ_pinName.insert(31, "DTR#");
    FT232RQ_pinName.insert(32, "RTS#");

    FT232RQ_mapping.insert(0, 30);
    FT232RQ_mapping.insert(1, 2);
    FT232RQ_mapping.insert(2, 32);
    FT232RQ_mapping.insert(3, 8);
    FT232RQ_mapping.insert(4, 31);
    FT232RQ_mapping.insert(5, 6);
    FT232RQ_mapping.insert(6, 7);
    FT232RQ_mapping.insert(7, 3);

    setFixedSize(width(), height());

    onChipChange(0);

    connect(ui.chipSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(onChipChange(int)));
    connect(ui.saveButton, SIGNAL(clicked()), this, SLOT(save()));

    foreach( QComboBox * cbox , pins){
        connect(cbox, SIGNAL(currentIndexChanged(int)), this, SLOT(pinAcquire(int)));
    }

    foreach (QToolButton * btn, resets) {
        connect(btn, SIGNAL(clicked()), this, SLOT(pinReleased()));
    }

    isAllPinsSet();

}

FTDIPinout::~FTDIPinout()
{

}


void FTDIPinout::initPins(unsigned char CSN, unsigned char SCK, unsigned char MOSI, unsigned char MISO, unsigned char CE)
{
	int index = ui.comboBox_CSN->findData(QVariant(toBitIndex(CSN)));
	if (index >= 0){
        qDebug() << "CSN" << index;
		ui.comboBox_CSN->setCurrentIndex(index);
	}
	
	index = ui.comboBox_SCK->findData(QVariant(toBitIndex(SCK)));
	if (index >= 0){
        qDebug() << "SCK" << index;
		ui.comboBox_SCK->setCurrentIndex(index);
	}

	index = ui.comboBox_MOSI->findData(QVariant(toBitIndex(MOSI)));
	if (index >= 0){
        qDebug() << "MOSI" << index;
		ui.comboBox_MOSI->setCurrentIndex(index);
	}

	index = ui.comboBox_MISO->findData(QVariant(toBitIndex(MISO)));
	if (index >= 0){
        qDebug() << "MISO" << index;
		ui.comboBox_MISO->setCurrentIndex(index);
	}

	index = ui.comboBox_CE->findData(QVariant(toBitIndex(CE)));
	if (index >= 0){
        qDebug() << "CE" << index;
		ui.comboBox_CE->setCurrentIndex(index);
	}

}

int FTDIPinout::getBit(QComboBox * cbox, int def){
    int index = cbox->currentIndex();
    if (index >= 0){
        return (1 << cbox->itemData(index).toInt());
    } else {
        return (1 << def);
    }
}

void FTDIPinout::isAllPinsSet()
{

    bool oneNotset = false;
    foreach (QComboBox * child, this->findChildren<QComboBox*>(QRegExp("comboBox_\\w+"))){
        int bitIndex = child->itemData(child->currentIndex()).toInt();
        if (bitIndex == -1){
            oneNotset = true;
            break;
        }
    }

    ui.saveButton->setEnabled(!oneNotset);

}

int FTDIPinout::getCE()
{
    return getBit(ui.comboBox_CE, CE_DEFAULT_BIT_INDEX);
}

int FTDIPinout::getSCK()
{
    return getBit(ui.comboBox_SCK, SCK_DEFAULT_BIT_INDEX);
}

int FTDIPinout::getMOSI()
{
    return getBit(ui.comboBox_MOSI, MOSI_DEFAULT_BIT_INDEX);
}

int FTDIPinout::getMISO()
{
    return getBit(ui.comboBox_MISO, MISO_DEFAULT_BIT_INDEX);
}

int FTDIPinout::getCSN()
{
    return getBit(ui.comboBox_CSN, CSN_DEFAULT_BIT_INDEX);
}

void FTDIPinout::save()
{
    /*
    foreach (QComboBox * child, this->findChildren<QComboBox*>(QRegExp("comboBox_\\w+"))){
        qDebug() << child->objectName();
        settings.setValue(child->objectName(), child->itemData(child->currentIndex()));
    }
    settings.setValue(ui.chipSelector->objectName(), ui.chipSelector->currentIndex());
    settings.sync();
    */
    accept();
}

void FTDIPinout::onChipChange(int index)
{
    QMap<int, int> * mapping = &FT232RL_mapping;
    QMap<int, QString> * nameMapping = &FT232RL_pinName;
    foreach( QComboBox * cbox , pins){
        cbox->clear();
        cbox->addItem("",-1);
        foreach (int keyBitIndex , mapping->keys()){
            int pin = mapping->value(keyBitIndex);
            cbox->addItem( nameMapping->value(pin), keyBitIndex );
        }
    }
}

void FTDIPinout::pinAcquire(int index)
{
    qDebug() << sender()->objectName() << (index-1);

    QComboBox * cbox = qobject_cast<QComboBox*>(sender());
    if (cbox){
        int prevPinIndex =  prevPin.contains(cbox) ? prevPin[cbox] : -1;
        int pinIndex = cbox->itemData(index).toInt();
        if (index >= 1){
            // disable others
            resets.value(pins.indexOf(cbox))->setEnabled(true);
            foreach( QComboBox * cboxOther , pins){
                if (cboxOther != cbox){
                    int indexToRemove = cboxOther->findData(QVariant(pinIndex));
                    if (indexToRemove > 0){
                        cboxOther->model()->setData(cboxOther->model()->index(indexToRemove, 0), QVariant(0), Qt::UserRole - 1);
                    }
                }
            }
        }
        // enable on reset
        if (prevPinIndex >= 0){
            foreach( QComboBox * cboxOther , pins){
                if (cboxOther != cbox){
                    cboxOther->model()->setData(cboxOther->model()->index(prevPinIndex+1, 0), QVariant(Qt::ItemIsSelectable | Qt::ItemIsEnabled), Qt::UserRole-1);
                }
            }
        }

        prevPin[cbox] = pinIndex;
    }

    isAllPinsSet();

}

void FTDIPinout::pinReleased()
{
    QToolButton * btn = qobject_cast<QToolButton*>(sender());
    if (btn){
        int index = resets.indexOf(btn);
        if (index >= 0){
            QComboBox * cbox = pins.value(index);
            if (cbox) cbox->setCurrentIndex(0);
            btn->setEnabled(false);
        }
    }

    isAllPinsSet();
}

int FTDIPinout::toBitIndex( unsigned char val)
{
	int i = 0;
	for (; i < 8; i++){
		if (val & (1 << i)) {
			return i;
		}
	}
	return -1;
}
