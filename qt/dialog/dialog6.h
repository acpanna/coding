#include <qdialog.h>
#include <qstring.h>
#include <qlineedit.h>
#include <qspinbox.h>

class AddressDialog : public QDialog
{
  Q_OBJECT

  public:
    AddressDialog(QWidget *parent = 0, const char *name = 0, WFlags f = 0);
    ~AddressDialog() {}

    QString name() { return nameW->text(); }
    QString email() { return emailW->text(); }
    int age() { return ageW->value(); }

  public slots:
    void clear();

  private:
    QLineEdit *nameW, *emailW;
    QSpinBox *ageW;
};
