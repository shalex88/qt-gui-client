#include <sstream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTcpSocket>
#include <QHostAddress>

class MyWindow : public QWidget {
public:
    MyWindow();

private slots:
    void onSendButtonClicked();
    void onReadyRead();

private:
    QLineEdit* input_line_edit_;
    QLabel* response_label_;
    QTcpSocket* tcp_socket_;
};

MyWindow::MyWindow() {
    auto* layout = new QVBoxLayout(this);
    input_line_edit_ = new QLineEdit(this);
    auto* send_button = new QPushButton("Send", this);
    response_label_ = new QLabel("Response will appear here", this);

    layout->addWidget(input_line_edit_);
    layout->addWidget(send_button);
    layout->addWidget(response_label_);

    tcp_socket_ = new QTcpSocket(this);

    connect(send_button, &QPushButton::clicked, this, &MyWindow::onSendButtonClicked);
    connect(tcp_socket_, &QTcpSocket::readyRead, this, &MyWindow::onReadyRead);

    const int tcp_server_port = 12345;
    tcp_socket_->connectToHost(QHostAddress::LocalHost, tcp_server_port);
}

void MyWindow::onSendButtonClicked() {
    QString text = input_line_edit_->text();
    if (!text.isEmpty()) {
        tcp_socket_->write(text.toUtf8());
    }
}

void MyWindow::onReadyRead() {
    QByteArray response_data = tcp_socket_->readAll();

    std::ostringstream os;
    os << "Received (" << response_data.length() << " bytes): ";

    os << std::string(response_data) << " [";

    for (int i = 0; i < response_data.length(); i++) {
        os << static_cast<int>(static_cast<unsigned char>(response_data[i]));
        if (i < response_data.length() - 1) {
            os << " ";
        }
    }

    os << "]";

    response_label_->setText(QString::fromStdString(os.str()));
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWindow window;
    window.show();

    return QApplication::exec();
}
