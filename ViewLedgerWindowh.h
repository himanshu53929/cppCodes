#ifndef VIEWLEDGERWINDOWH
#define VIEWLEDGERWINDOWH

#include <QMainWindow>

namespace Ui {
class ViewLedgerWindow;
}

class ViewLedgerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewLedgerWindow(QWidget *parent = nullptr);
    ~ViewLedgerWindow();

private slots:


private:
    Ui::ViewLedgerWindow *ui;
};

#endif // VIEWLEDGERWINDOWH
