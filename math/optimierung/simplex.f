C------------------------------------------------------------------------------
C     
C     SIMPLEXVERFAHREN MIT PHASE 1 ZUR LOESUNG VON 
C
C              MAXIMIERE C'*X
C              UNTER     A*X <=B, X>=0
C 
C     IN PHASE 1 WERDEN SOLANGE PIVOTOPERATIONEN DURCHGEFUEHRT BIS 
C     EINE ZULAESSIGE BASISLOESUNG GEFUNDEN WIRD. ANSCHLIESSEND WIRD 
C     DER SIMPLEXALGORITHMUS DURCHGEFUEHRT.
C
C     EINGABE:
C     IOUT      : INTEGER
C                 IOUT=0 : ES ERFOLGT KEINE AUSGABE DER TABLEAUS
C                 IOUT=1 : ES ERFOLGT EINE AUSGABE DER TABLEAUS
C     M         : INTEGER
C                 ANZAHL NEBENBEDINGUNGEN (ANZAHL DER ZEILEN VON A)
C     N         : INTEGER
C                 ANZAHL UNBEKANNTER (ANZAHL DER SPALTEN VON A)
C     A(M,N)    : DOUBLE
C                 MATRIX DER DIMENSION MxN
C     B(M)      : DOUBLE
C                 VEKTOR DER DIMENSION M
C     C(N)      : DOUBLE
C                 VEKTOR DER DIMENSION N
C
C     AUSGABE: 
C     X(N+M)    : DOUBLE
C                 VEKTOR DER DIMENSION M+N ENTHAELT DIE LOESUNG DES PROBLEMS 
C                 X(1)...X(N)     SIND DIE URSPRUENGLICHEN VARIABLEN, 
C                 X(N+1)...X(N+M) SIND SCHLUPFVARIABLE
C     IB(M)     : INTEGER 
C                 BASISINDEXMENGE
C     IN(N)     : INTEGER
C                 NICHTBASISINDEXMENGE
C     LAMBDA(M) : DOUBLE
C                 DUALE LOESUNG
C     
C------------------------------------------------------------------------------
C     ACHTUNG: A,B,C WERDEN UEBERSCHRIEBEN!
C------------------------------------------------------------------------------
      SUBROUTINE SIMPLEXPH1(IOUT,M,N,A,B,C,X,IB,IN,LAMBDA)
      IMPLICIT NONE
      INTEGER IOUT,M,N
      DOUBLE PRECISION B(M),A(M,N),C(N),X(N+M),LAMBDA(M)
C     LOKALE DATEN
      LOGICAL IFIRST,INSOLVE,IPHASE,LUNIQUE
      INTEGER I,J,P,Q,IHILF,ITAB,IB(*),IN(*),INMIN,IBMIN
      DOUBLE PRECISION D,CMAX,BMIN
      CHARACTER*80,CH,CH1
      ITAB=0
C     HILFSVARIABLE ZUR TABLEAUTRANSFORMATION
      D = 0.0D0
      DO 10,J=1,N
         IN(J) = J
 10   CONTINUE
      DO 30,I=1,M
         IB(I) = N+I
 30   CONTINUE
C     AUSGANGSTABLEAU AUFSTELLEN
      IF (IOUT.EQ.1) CALL TABLEAU(ITAB,N,M,IB,IN,C,B,A,D)
C     
C     ZULAESSIGKEITSALGORITHMUS
      IPHASE=.TRUE.
 1111 CONTINUE
      IBMIN=N+M+1
      DO 40,I=1,M
         IF (B(I).LT.-1.0D-10 .AND. IB(I).LT.IBMIN) THEN 
            P=I
            IBMIN = IB(I)
         ENDIF
 40   CONTINUE
      IF (IBMIN.EQ.M+N+1) THEN 
         IF (IOUT.EQ.1) 
     +        PRINT*,'BASISLOESUNG IST ZULAESSIG: STARTE OPTIMIERUNG'
         IPHASE=.FALSE.
         GOTO 450
      ENDIF
      INMIN=N+M+1
      DO 41,I=1,N
         IF (A(P,I).LT.-1.0D-10 .AND. IN(I).LT.INMIN) THEN 
            Q=I
            INMIN = IN(I)
         ENDIF
 41   CONTINUE
      IF (INMIN.EQ.M+N+1) THEN 
         PRINT*,'DAS PROBLEM IST UNZULAESSIG'
         RETURN
      ENDIF
      GOTO 999

C     PIVOTSPALTE BESTIMMEN
 450  CONTINUE
      INMIN=N+M
      Q=0
      DO 501,I=1,N
         IF (IN(I).LE.INMIN.AND.C(I).GT.1.0D-10) THEN 
            INMIN=IN(I)
            Q=I
         ENDIF
 501  CONTINUE
C     IST DAS TABLEAU OPTIMAL
      IF (Q.EQ.0) THEN 
         LUNIQUE=.TRUE.
         IF (IOUT.EQ.1) THEN 
            PRINT*
            PRINT*,'---------------------------------------------------'
            PRINT*,'DAS TABLEAU NR. ',ITAB,' IST OPTIMAL MIT F=',-D
            PRINT*
            PRINT*,'TYP IB/IN     PRIMAL              DUAL'
            PRINT*,'---------------------------------------------------'
         ENDIF
         DO 60,I=1,M
            X(IB(I))=B(I)
            IF (IB(I).LE.N) THEN 
               IF (IOUT.EQ.1) 
     +              WRITE(*,'(X,A1,3X,A1,I5,3X,2E20.8)') 'O','B',IB(I),
     +              X(IB(I)),0.0D0
            ELSE
               IF (IOUT.EQ.1)
     +              WRITE(*,'(X,A1,3X,A1,I5,3X,2E20.8)') 'S','B',IB(I),
     +              X(IB(I)),0.0D0
               LAMBDA(IB(I)-N)=0.0D0
            ENDIF
 60      CONTINUE         
         DO 70,I=1,N
            X(IN(I))=0.0D0
            IF (IN(I).LE.N) THEN 
               IF (IOUT.EQ.1) 
     +              WRITE(*,'(X,A1,3X,A1,I5,3X,2E20.8)') 'O','N',IN(I),
     +              X(IN(I)),-C(I)
            ELSE
               IF (IOUT.EQ.1) 
     +              WRITE(*,'(X,A1,3X,A1,I5,3X,2E20.8)') 'S','N',IN(I),
     +              X(IN(I)),-C(I)
               LAMBDA(IN(I)-N)=-C(I)
            ENDIF
            IF (DABS(C(I)).LE.1.0D-10) LUNIQUE=.FALSE.
 70      CONTINUE
         IF (.NOT.LUNIQUE .AND. IOUT.EQ.1) 
     +        WRITE(*,*) 'DIE LOESUNG IST NICHT EINDEUTIG!'
         RETURN
      ENDIF
C     PIVOTZEILE BESTIMMEN
      IFIRST=.TRUE.
      INSOLVE=.TRUE.
      IBMIN=N+M
      DO 700,I=1,M
         IF (A(I,Q).GT.1.0D-10) THEN
            IF (IFIRST) THEN 
               INSOLVE=.FALSE.
               IFIRST=.FALSE.
               BMIN=B(I)/A(I,Q)
               P=I
               IBMIN=IB(I)
            ELSE
               IF (B(I)/A(I,Q).LT.BMIN) THEN 
                  BMIN=B(I)/A(I,Q)
                  IBMIN=IB(I)
                  P=I
               ENDIF
               IF (DABS(B(I)/A(I,Q)-BMIN).LT.1.D-10 .AND. 
     +              IB(I).LT.IBMIN) THEN 
                  IBMIN=IB(I)
                  P=I
               ENDIF
            ENDIF
         ENDIF
 700  CONTINUE
      IF (INSOLVE) THEN 
         PRINT*,'DAS PROBLEM IST NICHT LOESBAR!'
         RETURN
      ENDIF
 999  CONTINUE
      IF (IOUT.EQ.1) THEN 
         PRINT*,'PIVOTZEILE UND -SPALTE IN ITERATION ',ITAB+1,':',P,Q
         PRINT*,'PIVOTELEMENT A(P,Q): ',A(P,Q)
      ENDIF
C     AUSTAUSCHSCHRITT
      D=D-C(Q)*B(P)/A(P,Q)
      DO 800,J=1,N
         IF (J.NE.Q) THEN 
            C(J)=C(J)-C(Q)*A(P,J)/A(P,Q)
         ENDIF         
 800  CONTINUE
      C(Q)=-C(Q)/A(P,Q)
      DO 810,I=1,M
         IF (I.NE.P) THEN 
            B(I)=B(I)-A(I,Q)*B(P)/A(P,Q)
         ENDIF
 810  CONTINUE
      B(P)=B(P)/A(P,Q)
      DO 820,I=1,M
         DO 830,J=1,N
            IF (I.NE.P .AND. J.NE.Q) THEN 
               A(I,J)=A(I,J)-A(I,Q)*A(P,J)/A(P,Q)
            ENDIF
 830     CONTINUE
 820  CONTINUE
      DO 840,I=1,M
         IF (I.NE.P) A(I,Q)=-A(I,Q)/A(P,Q)
 840  CONTINUE
      DO 850,J=1,N
         IF (J.NE.Q) A(P,J)=A(P,J)/A(P,Q)
 850  CONTINUE
      A(P,Q)=1.0D0/A(P,Q)
      IHILF=IB(P)
      IB(P)=IN(Q)
      IN(Q)=IHILF
C     AUSGABE
      IF (IOUT.EQ.1) CALL TABLEAU(ITAB,N,M,IB,IN,C,B,A,D)
      ITAB=ITAB+1
      IF (IPHASE) THEN 
         GOTO 1111
      ELSE
         GOTO 450
      ENDIF
C
C     ENDE: SIMPLEX
      RETURN
      END
C -----------------------------------------------------------------------------
C
C     AUSGABE DES TABLEAUS (STANDARDSIMPLEX)
C     
C -----------------------------------------------------------------------------
      SUBROUTINE TABLEAU(ITAB,N,M,IB,IN,C,B,A,D)
      IMPLICIT NONE
      INTEGER ITAB,IB(*),IN(*),N,M
      DOUBLEPRECISION C(*),B(*),A(M,*),D
C
C     LOKALE DATEN
      INTEGER I,J
      CHARACTER*80,CH,CH1
      PRINT*
      PRINT*,'____________________________________________________'
      PRINT*,'TABLEAU ',ITAB+1
      PRINT*,'____________________________________________________'
      WRITE(*,*)
      WRITE(CH1,*) '(',15*(N+1)+6,'A1)'
      WRITE(CH,*) '(',N,'I15)'
      WRITE(*,CH) (IN(I),I=1,N)
      WRITE(*,CH1) ('-',I=1,15*(N+1)+6)
      WRITE(CH,*) '(',N,'E15.3,4X,A2,E15.3,I4)'
      WRITE(*,CH) ((A(I,J),J=1,N),'|',B(I),IB(I),I=1,M)
      WRITE(*,CH1) ('-',I=1,15*(N+1)+6)
      WRITE(CH,*) '(',N,'E15.3,4X,A2,E15.3)'
      WRITE(*,CH) (C(I),I=1,N),'|',D
      WRITE(*,*)
C
C     ENDE: TABLEAU
      RETURN
      END

