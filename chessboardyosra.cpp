#include "mainwindowyosra.h"
#include "chessboardyosra.h"
#include "ui_chessboardyosra.h"

//_______________________________CHESSBOARD_________________________________
/**
 * @brief ChessBoard::ChessBoard, constructor of chessboard
 * @param file, file to load to place the piece
 * @param parent, the parent object
 */
ChessBoardyosra::ChessBoardyosra(QString file,QWidget *parent):
    QDialog(parent),
    ui(new  Ui::ChessBoardyosra){
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->posDeadPiece.setX(0);
    this->posDeadPiece.setY(2);
    this->player1 = new Playerjeu(0);
    this->player2 = new Playerjeu(1);
    this->currentPlayer=this->player1;
    this->initGame(file);
    this->initPlayers();

    connect(this,SIGNAL(maxAtteint()),this,SLOT(upgradePion()));
}

//_______________________________METHOD_________________________________
/**
 * @brief ChessBoard::upgradePion, améliore en une autre pièce le pion quand il atteint la dernière rangée adverse
 */
void ChessBoardyosra::upgradePion(){

    //cout << "methode slot appelé" << endl;
    ChoixUpgrade *choix = new ChoixUpgrade;
    connect(choix,SIGNAL(btn_reine_clicked()),this,SLOT(transformToReine()));
    connect(choix,SIGNAL(btn_tour_clicked()),this,SLOT(transformToTour()));
    connect(choix,SIGNAL(btn_cavalier_clicked()),this,SLOT(transformToCavalier()));
    connect(choix,SIGNAL(btn_fou_clicked()),this,SLOT(transformToFou()));
    choix->exec();
}

/**
 * @brief ChessBoard::~ChessBoard, destructor of chessboard
 */
ChessBoardyosra::~ChessBoardyosra()
{
    delete ui;
}

/**
 * @brief ChessBoard::transformToReine, transform the current piece to a queen
 */
void ChessBoardyosra::transformToReine(){
    /**
     * @brief reine, créatipn d'une reine avec comme couleur et comme position celle de la pièce sélectionnée
     */
    Reine *reine = new Reine(this,this->selectedPiece->getColor(),this->selectedPiece->getOwner(),this->selectedPiece->getWidth(),this->selectedPiece->getHeigth(),this->selectedPiece->getTabPosX()*TAILLECASE+25,this->selectedPiece->getTabPosY()*TAILLECASE);
    reine->setTabPosX(this->selectedPiece->getTabPosX());
    reine->setTabPosY(this->selectedPiece->getTabPosY());

    //Ajoute la nouvelle pièce créée dans le tableau de pièece de chessboard et du tableau de pièce du joueur
    this->pieces.push_back(reine);
    reine->getOwner()->addPiece(reine);

    this->chessBoard[reine->getTabPosX()][reine->getTabPosY()] = reine->getPieceName(); //On remplace le caractère de la pièce actuelle par celle qui vient d'être créé

    //On supprime l'ancienne pièce des tableaux de chessboard et player
    this->removePiece(this->selectedPiece);
    reine->getOwner()->removePiece(this->selectedPiece);
    delete this->selectedPiece;
    this->selectedPiece = reine; //On indique que la pièce sélectionnée est celle qui vient d'être créé
}

/**
 * @brief ChessBoard::transformToCavalier, transform the current piece to a knigth
 */
void ChessBoardyosra::transformToCavalier(){
    /**
     * @brief cavalier, création d'un cavalier avec comme couleur et comme position celle de la pièce sélectionnée
     */
    Cavalier *cavalier = new Cavalier(this,this->selectedPiece->getColor(),this->selectedPiece->getOwner(),this->selectedPiece->getWidth(),this->selectedPiece->getHeigth(),this->selectedPiece->getTabPosX()*TAILLECASE+25,this->selectedPiece->getTabPosY()*TAILLECASE);
    cavalier->setTabPosX(this->selectedPiece->getTabPosX());
    cavalier->setTabPosY(this->selectedPiece->getTabPosY());


    //Ajoute la nouvelle pièce créée dans le tableau de pièece de chessboard et du tableau de pièce du joueur
    this->pieces.push_back(cavalier);
    cavalier->getOwner()->addPiece(cavalier);
    this->chessBoard[cavalier->getTabPosX()][cavalier->getTabPosY()] = cavalier->getPieceName();//On remplace le caractère de la pièce actuelle par celle qui vient d'être créé

    //On supprime l'ancienne pièce des tableaux de chessboard et player
    this->removePiece(this->selectedPiece);
    cavalier->getOwner()->removePiece(this->selectedPiece);
    delete this->selectedPiece;
    this->selectedPiece = cavalier; //On indique que la pièce sélectionnée est celle qui vient d'être créé
}

/**
 * @brief ChessBoard::transformToFou, transform the current piece to a bishop
 */
void ChessBoardyosra::transformToFou(){

    /**
     * @brief fou, création d'un fou avec comme couleur et comme position celle de la pièce sélectionnée
     */
    Fou *fou = new Fou(this,this->selectedPiece->getColor(),this->selectedPiece->getOwner(),this->selectedPiece->getWidth(),this->selectedPiece->getHeigth(),this->selectedPiece->getTabPosX()*TAILLECASE+25,this->selectedPiece->getTabPosY()*TAILLECASE);
    fou->setTabPosX(this->selectedPiece->getTabPosX());
    fou->setTabPosY(this->selectedPiece->getTabPosY());


    //Ajoute la nouvelle pièce créée dans le tableau de pièece de chessboard et du tableau de pièce du joueur
    this->pieces.push_back(fou);
    fou->getOwner()->addPiece(fou);
    this->chessBoard[fou->getTabPosX()][fou->getTabPosY()] = fou->getPieceName(); //On remplace le caractère de la pièce actuelle par celle qui vient d'être créé

    //On supprime l'ancienne pièce des tableaux de chessboard et player
    this->removePiece(this->selectedPiece);
    fou->getOwner()->removePiece(this->selectedPiece);
    delete this->selectedPiece;
    this->selectedPiece = fou; //On indique que la pièce sélectionnée est celle qui vient d'être créé
}

/**
 * @brief ChessBoard::transformToTour, transform the current piece to a rook
 */
void ChessBoardyosra::transformToTour(){

    /**
     * @brief tour, création d'une tour avec comme couleur et comme position celle de la pièce sélectionnée
     */
    Tour *tour = new Tour(this,this->selectedPiece->getColor(),this->selectedPiece->getOwner(),this->selectedPiece->getWidth(),this->selectedPiece->getHeigth(),this->selectedPiece->getTabPosX()*TAILLECASE+25,this->selectedPiece->getTabPosY()*TAILLECASE);
    tour->setTabPosX(this->selectedPiece->getTabPosX());
    tour->setTabPosY(this->selectedPiece->getTabPosY());

    //Ajoute la nouvelle pièce créée dans le tableau de pièece de chessboard et du tableau de pièce du joueur
    this->pieces.push_back(tour);
    tour->getOwner()->addPiece(tour);
    this->chessBoard[tour->getTabPosX()][tour->getTabPosY()] = tour->getPieceName(); //On remplace le caractère de la pièce actuelle par celle qui vient d'être créé

    //On supprime l'ancienne pièce des tableaux de chessboard et player
    this->removePiece(this->selectedPiece);
    tour->getOwner()->removePiece(this->selectedPiece);
    delete this->selectedPiece;
    this->selectedPiece = tour; //On indique que la pièce sélectionnée est celle qui vient d'être créé
}

/**
 * @brief ChessBoard::paintEvent, the paintEvent is called when the signal update() is called. This method is used to draw the case of the chessboard and the case for move
 */
void ChessBoardyosra::paintEvent(QPaintEvent *)
{
    //Permet de dessiner les cases de l'échiquier en alternant les couleurs
    QPainter painter(this);
    for(int i=0; i<8 ; i++){
        for(int j=0; j<8; j++){
            if(i%2==0){
                if(j%2==0){
                    caseBoard[i][j] = new Case(TAILLECASE,i*TAILLECASE,j*TAILLECASE);
                    caseBoard[i][j]->draw(&painter, QColor(36,68,92));
                }else{
                    caseBoard[i][j] = new Case(TAILLECASE,i*TAILLECASE,j*TAILLECASE);
                    caseBoard[i][j]->draw(&painter, QColor(206,206,206));
                }
            }else{
                if(j%2==0){
                    caseBoard[i][j]= new Case(TAILLECASE,i*TAILLECASE,j*TAILLECASE);
                    caseBoard[i][j]->draw(&painter, QColor(206,206,206));

                }else{
                    caseBoard[i][j]=new Case(TAILLECASE,i*TAILLECASE,j*TAILLECASE);
                    caseBoard[i][j]->draw(&painter, QColor(36,68,92));
                }
            }
        }
    }

    //Si une pièce est selectionnée, dessine tous les mouvements possibles présents dans le tableau allPossibleMove de cette dernière
    if(this->selectedPiece)
    {
        for(unsigned int i=0; i< this->selectedPiece->allPossibleMove.size();i++){
            this->possibleMove.push_back( new Case(TAILLECASE,this->selectedPiece->allPossibleMove.at(i).x()*TAILLECASE,this->selectedPiece->allPossibleMove[i].y()*TAILLECASE));
            this->possibleMove.at(i)->draw(&painter, QColor(255,87,51,150));

        }
    }
}

//____________________________________________________________DEPLACEMENT PIECE___________________________________________________
/**
 * @brief ChessBoard::mousePressEvent, this event is called when the user interact with the mouse. This event is used to select a piece and for move it.
 * @param event
 */
void ChessBoardyosra::mousePressEvent(QMouseEvent *event){
    /**Action à effectuer lors d'un clic gauche de la souris
     * Lorqu'un clic gauche est détecté et qu'il n'y a aucune pièce sélectionnée actuellement :
     * - Si le clic gauche est sur une pièce sélectionne la pièce
     * - Sinon il ne se passe rien
     *
     * Losqu'un clic gauche est détecté et qu'une pièce a été précèdemment sélectionne :
     * - Si le clic est sur un des mouvements valide de la pièce, cela déplace donc la pièce à la case sélectionné
     * - Sinon déselectionne la pièce
    **/
    if(event->buttons() & Qt::LeftButton ){
        if(this->selectedPiece){
            //Vérifie que la case cliquée est bien un mouvement valide de la pièce
            if(this->selectedPiece->isValidMove(floor(event->x()/TAILLECASE),floor(event->y()/TAILLECASE),this->pieces) && !this->selectedPiece->getOwner()->getHasPlayed())
            {

                ///***Détruire la pièce si elle est mangée***///
                Piece * test = this->getPieceAt((int)floor(event->x()/TAILLECASE),(int)floor(event->y()/TAILLECASE));
                if(test && test!=this->selectedPiece && test->getOwner()!=this->selectedPiece->getOwner()){
                    test->move(this->posDeadPiece.x()+8,this->posDeadPiece.y());

                    //Positionne la pièce détruite en dehors du plateau
                    this->posDeadPiece.setX(this->posDeadPiece.x()+1);
                    if(this->posDeadPiece.x()%6==0){
                        this->posDeadPiece.setY(this->posDeadPiece.y()+1);
                        this->posDeadPiece.setX(0);
                    }
                    //Si la pièce détruite est le roi du joueur adverse, affiche une pop-up indiquant le joueur ayant gagné et retourne au menu principal
                    if(test->getIsKing())
                    {
                        //Création de la fenêtre
                        QMessageBox *msg = new QMessageBox(this);
                        QString test("Joueur ");
                        test+=QString::number(this->selectedPiece->getOwner()->getId()+1);
                        test.operator +=(" a gagné !");

                        msg->setText(test);
                        msg->addButton("Ok",QMessageBox::AcceptRole);
                        msg->exec();
                        this->close();
                        //Retour au menu
                        MainMenu menu;
                        menu.exec();
                    }

                    //On enlève la pièce du tableau de pièce jouable
                    this->removePiece(test);

                    //On enlève la pièce du tableau de pièce jouable du joueur
                    this->selectedPiece->getOwner()->removePiece(test);
                }

                ///*****************************************///

                ///*****Gestion du déplacement de la pièce*****///
                this->selectedPiece->move(floor(event->x()/TAILLECASE),floor(event->y()/TAILLECASE));
                this->chessBoard[(int)(floor(this->selectedPiece->getOldY()/TAILLECASE))][(int)(floor(this->selectedPiece->getOldX()/TAILLECASE))] = '0';
                this->chessBoard[(int)floor(event->y()/TAILLECASE)][(int)floor(event->x()/TAILLECASE)] = this->selectedPiece->getPieceName();

                ///********************************************///

                //Emet le signal maxAtteint lorsqu'un pion atteint la dernière rangée adverse afin de l'améliorer en une autre pièce
                if(this->selectedPiece->getIsPion() && (this->selectedPiece->getTabPosY()==7 || this->selectedPiece->getTabPosY()==0))
                    emit maxAtteint();

                ///******Gestion tour joueur******///
                this->currentPlayer->setHasPlayed(true);
                if(this->currentPlayer==this->player1){
                    this->currentPlayer=this->player2;
                    ui->namePlayer->setText("Joueur 2");
                }else{
                    this->currentPlayer=this->player1;
                    ui->namePlayer->setText("Joueur 1");
                }
                this->currentPlayer->setHasPlayed(false);

                ///******************************///

            }

            //Suppression de tous les mouvements possible de la pièce
            this->selectedPiece->allPossibleMove.clear();
            this->possibleMove.clear();
            this->selectedPiece = NULL;
            //On redéssine le plateau afin d'enlever les cases de couleurs indiquant les déplacements possibles de la pièce
            this->update();
        }
        else{
            //Compare la position du curseur de la souris avec la position de toutes les pièces jouables afin de déterminer quelle pièce est sélectionnée
            for(unsigned int i=0;i<this->pieces.size();i++){
                if(this->currentPlayer==this->pieces[i]->getOwner() && (event->x() > this->pieces.at(i)->getTabPosX()*TAILLECASE+
                     CHESSBOARD_POS.x() && event->x() <this->pieces.at(i)->getTabPosX()*TAILLECASE+TAILLECASE+CHESSBOARD_POS.x() &&
                     event->y() > this->pieces.at(i)->getY() && event->y() < this->pieces.at(i)->getTabPosY()*TAILLECASE+TAILLECASE+
                     CHESSBOARD_POS.y())){
                        this->selectedPiece = this->pieces.at(i);
                        this->selectedPiece->setOldX(event->x());
                        this->selectedPiece->setOldY(event->y());

                    //Si un pion est sélectionné, on regarde si ce dernier peut attaqué ou non
                    if(this->selectedPiece->getIsPion()){
                        Pion *pion = static_cast<Pion *>(this->selectedPiece);
                        pion->canAttack(this->chessBoard);
                    }

                    this->selectedPiece->pos.setX(this->selectedPiece->getTabPosX());
                    this->selectedPiece->pos.setY(this->selectedPiece->getTabPosY());
                    QPoint p(this->selectedPiece->operator -(QPoint(4,4)));
                    this->selectedPiece->updateAllPossibleMove(this->pieces);
                    this->update();

                }

            }

        }
    }
}

//____________________________________________________________INITIALISATION JEU__________________________________________________
/**
 * @brief ChessBoard::initGame, permet d'initialiser les différents pièces sur le tableau
 * @param fichier, fichier lu pour l'initialisation des pièces
 */
void ChessBoardyosra::initGame(QString fichier){
    this->lectureFichier(fichier.toStdString());
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
            cout << chessBoard[i][j] << " ";
        cout << endl;
    }

    //Instancie les différentes pièces en fonction des charactères du fichier
    for(int i=0; i<8;i++){
        for(int j=0; j<8;j++){
            switch(chessBoard[i][j])
            {
            case '1':
            {
                Pion *pion = new Pion(this,"Blanc",this->player1,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                pion->setTabPosX(j);
                pion->setTabPosY(i);
                this->pieces.push_back(pion);
                break;
            }
            case '2' :
            {
                Cavalier *cavalier = new Cavalier(this,"Blanc",this->player1 ,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                cavalier->setTabPosX(j);
                cavalier->setTabPosY(i);
                this->pieces.push_back(cavalier);
                break;
            }
            case '3' :
            {
                Tour *tour = new Tour(this,"Blanc",this->player1 ,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                tour->setTabPosX(j);
                tour->setTabPosY(i);
                this->pieces.push_back(tour);
                break;
            }
            case '4' :
            {
                Fou *fou = new Fou(this,"Blanc",this->player1 ,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                fou->setTabPosX(j);
                fou->setTabPosY(i);
                this->pieces.push_back(fou);
                break;
            }
            case '5' :
            {
                Reine *reine = new Reine(this,"Blanc",this->player1 ,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                reine->setTabPosX(j);
                reine->setTabPosY(i);
                this->pieces.push_back(reine);
                break;
            }
            case '6' :
            {
                Roi *roi = new Roi(this,"Blanc",this->player1 ,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                roi->setTabPosX(j);
                roi->setTabPosY(i);
                this->pieces.push_back(roi);
                break;
            }
            case 'p' :
            {
                Pion *pion2 = new Pion(this,"Noir",this->player2 ,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                pion2->setTabPosX(j);
                pion2->setTabPosY(i);
                this->pieces.push_back(pion2);
                break;
            }
            case 't' :
            {
                Tour *tour = new Tour(this,"Noir",this->player2 ,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                tour->setTabPosX(j);
                tour->setTabPosY(i);
                this->pieces.push_back(tour);
                break;
            }
            case 'c' :
            {
                Cavalier *cavalier = new Cavalier(this,"Noir",this->player2 ,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                cavalier->setTabPosX(j);
                cavalier->setTabPosY(i);
                this->pieces.push_back(cavalier);
                break;
            }
            case 'f' :
            {
                Fou *fou = new Fou(this,"Noir",this->player2 ,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                fou->setTabPosX(j);
                fou->setTabPosY(i);
                this->pieces.push_back(fou);
                break;
            }
            case 'k' :
            {
                Roi *roi = new Roi(this,"Noir",this->player2 ,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                roi->setTabPosX(j);
                roi->setTabPosY(i);
                this->pieces.push_back(roi);
                break;
            }
            case 'q' :
            {
                Reine *reine = new Reine(this,"Noir",this->player2 ,50,50,j*TAILLECASE+CENTRER_PIECE+CHESSBOARD_POS.x(),i*TAILLECASE+CHESSBOARD_POS.y());
                reine->setTabPosX(j);
                reine->setTabPosY(i);
                this->pieces.push_back(reine);
                break;
            }
            }
        }
    }
}



//____________________________________________________________GESTION LECTURE FICHIER___________________________________________________

/**
 * @brief ChessBoard::lectureFichier, permet de lire un fichier
 * @param sauvegarde, nom du fichier de sauvegarde
 */
void ChessBoardyosra::lectureFichier(string sauvegarde){

    //Si le fichier n'est pas présent, on déclenche une exception
    try{
        ifstream fichier(sauvegarde, ios::in);  // on ouvre le fichier en lecture
        string ligne;
        if(!fichier)
            throw QException();

        for(int i=0;i<8;i++){
            getline(fichier, ligne);
            for(int j=0;j<8;j++){
                this->chessBoard[i][j] = ligne[j];
            }
        }
        getline(fichier,ligne);
        cout << "ligne = " << ligne[0] << endl;
        if(ligne[0]=='j')
            this->currentPlayer=this->player2;
        else
            this->currentPlayer=this->player1;

        fichier.close();
    }catch(QException e){
        QMessageBox *msg = new QMessageBox(this);
        msg->setText("Fichier non trouvé");
        msg->exec();

        //Initialisation de l'échiquier
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                this->chessBoard[i][j] = '0';

        //Lorsque le fichier n'est pas trouvé, on le recréé en ajoutant la position de base des pièces
        this->chessBoard[0][0] = '3';
        this->chessBoard[0][1] = '2';
        this->chessBoard[0][2] = '4';
        this->chessBoard[0][3] = '6';
        this->chessBoard[0][4] = '5';
        this->chessBoard[0][5] = '4';
        this->chessBoard[0][6] = '2';
        this->chessBoard[0][7] = '3';

        this->chessBoard[7][0] = 't';
        this->chessBoard[7][1] = 'c';
        this->chessBoard[7][2] = 'f';
        this->chessBoard[7][3] = 'k';
        this->chessBoard[7][4] = 'q';
        this->chessBoard[7][5] = 'f';
        this->chessBoard[7][6] = 'c';
        this->chessBoard[7][7] = 't';


        for(int i=0;i<8;i++)
        {
            this->chessBoard[1][i] = '1';
            this->chessBoard[6][i] = 'p';
        }

        //Ecriture du fichier d'initialisation
        this->ecritureFichierSauvegarde("initialisation.txt");


    }
}

/**
 * @brief ChessBoard::ecritureFichierSauvegarde, permet d'écrire dans un fichier
 * @param fileName, nom du fichier dans lequel il faut écrire
 */
void ChessBoardyosra::ecritureFichierSauvegarde(QString fileName)
{
    try{
        ofstream fichier(fileName.toStdString(), ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

        //Si le fichier n'est pas présent, on déclenche une exception
        if(!fichier)
            throw QException();

        for (int cpt1=0; cpt1<8 ;cpt1++ )
        {
            for (int cpt2=0; cpt2<8 ;cpt2++ )
            {
                fichier<<chessBoard[cpt1][cpt2];
            }

            fichier<<endl;
        }
        if(this->currentPlayer==this->player1)
            fichier<<'9';
        else
            fichier<<'j';
        fichier.close();
    }catch (QException e){
        //Indique que le fichier de sauvegarde n'est pas présent dans une pop up
        QMessageBox *msg = new QMessageBox(this);
        msg->setText("Impossible de trouver le fichier sauvegarde");
        msg->exec();
    }
}


/**
 * @brief ChessBoard::on_boutonSauvegarder_clicked, sauvegarde la partie dans le fichier de sauvegarde lors de l'appui sur le bouton sauvegarder
 */
void ChessBoardyosra::on_boutonSauvegarder_clicked()
{
    this->ecritureFichierSauvegarde("sauvegarde.txt");
}


/**
 * @brief ChessBoard::on_pushButton_clicked, ferme la fenêtre lors de l'appui du bouton quitter
 */
void ChessBoardyosra::on_pushButton_clicked()
{
    this->close();
    MainMenu menu;
    menu.exec();
}

/**
 * @brief ChessBoard::initPlayers, permet d'initialiser les tableaux de pièces de chaque joueurs
 */
void ChessBoardyosra::initPlayers(){
    for(unsigned int i=0;i<this->pieces.size();i++){
        if(this->pieces[i]->getOwner()==this->player1){
            this->player1->addPiece(this->pieces[i]);
        }else{
            this->player2->addPiece(this->pieces[i]);
        }
    }
}

/**
 * @brief ChessBoard::getPieceAt, récupères la pièce à la position (x,y) passé en paramètre
 * @param x, position x de la pièce
 * @param y, position y de la pièce
 * @return la pièce se situant à la position (x,y) ou null s'il n'y a aucune pièce
 */
Piece * ChessBoardyosra::getPieceAt(int x, int y){
    for(unsigned int i=0;i<this->pieces.size();i++)
    {
        if(x==this->pieces[i]->getTabPosX() && y==this->pieces[i]->getTabPosY())
        {
            return this->pieces[i];
        }
    }
    return 0;
}

/**
 * @brief ChessBoard::removePiece, supprime la pièce du tableau de pièce
 * @param piece, pièce à supprimer
 */
void ChessBoardyosra::removePiece(Piece *piece){
    for(std::vector<Piece *>::iterator it = pieces.begin() ; it < pieces.end(); it++)
        if(piece==*it){
            this->pieces.erase(it);
        }
}
