#include <vector>
#include <numeric>
#include <QThread>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./cards.h"

//vars
std::vector<int> dealerCards;
std::vector<QWidget*> dealerCardModels;
std::vector<int> playerCards;
std::vector<QWidget*> playerCardModels;

int dealerAmt = std::reduce(dealerCards.begin(), dealerCards.end());
int playerAmt = std::reduce(playerCards.begin(), playerCards.end());
int betAmount = 1;
bool dealerCanGo = true;
bool userWon = false;

// updates vars and checks status for game
void MainWindow::checkStatus() {
    dealerAmt = std::reduce(dealerCards.begin(), dealerCards.end());
    playerAmt = std::reduce(playerCards.begin(), playerCards.end());
    ui->dealerLabel->setText("Dealer: " + QString::number(dealerAmt));
    ui->playerLabel->setText("Player: " + QString::number(playerAmt));

    // checks win/lose conditions
    if ((playerAmt > 21 || dealerAmt == 21) || (!dealerCanGo && dealerAmt >= playerAmt)) {
        ui->hitButton->setEnabled(false);
        ui->standButton->setEnabled(false);
        timer->stop();

        //single shot pauses game for x milliseconds
        QTimer::singleShot(1500, this, [=](){
            ui->winWidget->setVisible(true);
            ui->winWidget->setStyleSheet("background-color: #FF0000;");
            ui->winLabel->setText("You Lose!");
            ui->moneyLabel->setText("You lost " + QString::number(betAmount) + " Duhblooniess");
            qInfo() << "YOU LOSE!" << Qt::endl;
        });
    } else if ((dealerAmt > 21 || playerAmt == 21) || (!dealerCanGo && playerAmt > dealerAmt)) {
        ui->hitButton->setEnabled(false);
        ui->standButton->setEnabled(false);
        timer->stop();

        QTimer::singleShot(1500, this, [=](){
            ui->winWidget->setVisible(true);
            ui->winWidget->setStyleSheet("background-color: #00FF00;");
            userWon = true;
            ui->moneyLabel->setText("You won " + QString::number(betAmount * 2) + " Duhblooniess");
            ui->winLabel->setText("You Win!");
            qInfo() << "You WIN!" << Qt::endl;
        });
    }
}

//gets text inside of cards, and changes them to the correct value
void modifyCardLabels(QWidget* curCard, int val){
    QList<QLabel*> labels = curCard->findChildren<QLabel*>();

    for (QLabel* label: labels) {
        label->setText(QString::number(val));
    }
}

//creates new card whenever hit/stand is clicked
QWidget* createNewCard(bool isPlayerCard) {
    int randCard = getRandomCard();

    // Create the card widget
    QWidget* newCard = new QWidget();
    newCard->setFixedSize(100, 175);
    newCard->setStyleSheet("background-color: white;");

    // Create label 1 (top-left)
    QLabel* cardLabel1 = new QLabel(QString::number(randCard), newCard);
    cardLabel1->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    cardLabel1->setStyleSheet("font: 900 24pt 'Segoe UI'; color: black;");
    cardLabel1->setGeometry(10, 10, 40, 40);  // position inside card

    // Create label 2 (bottom-right)
    QLabel* cardLabel2 = new QLabel(QString::number(randCard), newCard);
    cardLabel2->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    cardLabel2->setStyleSheet("font: 900 24pt 'Segoe UI'; color: black;");
    cardLabel2->setGeometry(50, 125, 40, 40); // position inside card

    //adds to correct vector depending on if its a player's card
    if (isPlayerCard) {
        playerCards.push_back(randCard);
        playerCardModels.push_back(newCard);
    } else {
        dealerCards.push_back(randCard);
        dealerCardModels.push_back(newCard);
    }

    return newCard;
}

//plays through dealer's turn
void MainWindow::handleDealerTurn() {
    if (dealerAmt <= 16) {
        QWidget* newCard = createNewCard(false);
        ui->dealerLayout->insertWidget(0, newCard);
    } else {
        dealerCanGo = false;
    }
    checkStatus();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //basic styling
    this->setStyleSheet("background-color: #2d5a5b;");
    ui->winWidget->setVisible(false);

    //connects original card models to vectors
    dealerCardModels.push_back(ui->cardWidget_1);
    dealerCardModels.push_back(ui->cardWidget_2);
    playerCardModels.push_back(ui->cardWidget_3);
    playerCardModels.push_back(ui->cardWidget_4);

    // sets up timer for dealer's turn, will run handleDealerTurn whenever timer is called
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::handleDealerTurn);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_hitButton_clicked() {
    // gets new card for user and adds it
    QWidget* newCard = createNewCard(true);
    ui->playerLayout->addWidget(newCard);
    checkStatus();
}

void MainWindow::on_standButton_clicked(){
    // gets new card for dealer and adds it
    ui->hitButton->setEnabled(false);
    ui->standButton->setEnabled(false);

    //runs handleDealerTurn every 1.5 seconds until stopped.
    timer->start(1500);
}

void MainWindow::on_betSpinBox_valueChanged(int arg1) {
    // updates bet value
    betAmount = arg1;
}

void MainWindow::on_confirmBetButton_clicked()
{
    betAmount = ui->betSpinBox->value();
    ui->betLabel->setText("Bet: " + QString::number(betAmount) + " Duhblooniess");

    // gets the cards for both people
    for(int i = 0; i < 4; i++) {

        int randCard = getRandomCard();
        int ind = i / 2;
        QWidget* curCard;
        // adds to the correct list, so each has two cards
        if (i % 2 == 0) {
            dealerCards.push_back(randCard);
            curCard = dealerCardModels[ind];
        } else {
            playerCards.push_back(randCard);
            curCard = playerCardModels[ind];
        }
        //sets labels to correct value
        modifyCardLabels(curCard, randCard);
        checkStatus();
    }

    // updates score labels, and displays game
    ui->dealerLabel->setText("Dealer: " + QString::number(dealerAmt));
    ui->playerLabel->setText("Player: " + QString::number(playerAmt));
    ui->betWidget->setVisible(false);
    checkStatus();
}

void MainWindow::on_quitButton_clicked() {
    // closes game
    QApplication::quit();
}

//resets game for another playthrough
void MainWindow::on_playAgainButton_clicked() {
    ui->betSpinBox->setValue(userWon ? betAmount * 2 : betAmount);

    // reset vars
    betAmount = 0;
    dealerAmt = 0;
    playerAmt = 0;
    dealerCanGo = true;
    userWon = false;

    // Delete extra UI elements for both dealer/user
    if (dealerCardModels.size() > 2) {
        for (auto it = dealerCardModels.begin() + 2; it != dealerCardModels.end(); ++it) {
            ui->dealerLayout->removeWidget(*it);
            delete *it;
        }
        dealerCardModels.erase(dealerCardModels.begin() + 2, dealerCardModels.end());
    }
    dealerCards.erase(dealerCards.begin(), dealerCards.end());

    if (playerCardModels.size() > 2) {
        for (auto it = playerCardModels.begin() + 2; it != playerCardModels.end(); ++it) {
            ui->playerLayout->removeWidget(*it);
            delete *it;
        }
        playerCardModels.erase(playerCardModels.begin() + 2, playerCardModels.end());
    }
    playerCards.erase(playerCards.begin(), playerCards.end());

    for (int i = 0; i < 2; ++i) {
        modifyCardLabels(dealerCardModels[i], 0);
        modifyCardLabels(playerCardModels[i], 0);
    }

    // Reset labels and restart
    checkStatus();
    ui->dealerLabel->setText("Dealer: " + QString::number(dealerAmt));
    ui->playerLabel->setText("Player: " + QString::number(playerAmt));

    QTimer::singleShot(250, this, [=] {
        ui->hitButton->setEnabled(true);
        ui->standButton->setEnabled(true);
        ui->betWidget->setVisible(true);
        ui->winWidget->setVisible(false);
    });
}
