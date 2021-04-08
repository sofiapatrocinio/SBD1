-- --------     << Sofia Patrocínio >>     ------------
-- 
-- SCRIPT DE CRIACAO (DDL)
-- 
-- Data Criacao ...........: 06/04/2021
-- Autor(es) ..............: Sofia Costa Patrocínio
-- Banco de Dados .........: MySQL 8.0.23
-- Banco de Dados(nome) ...: SofiaPatrocinio
-- 
-- PROJETO => 01 Base de Dados
--         => 05 Tabelas
-- -----------------------------------------------------------------

CREATE DATABASE IF NOT EXISTS SofiaPatrocinio;
USE SofiaPatrocinio;

CREATE TABLE INTERNAUTA (
    apelido VARCHAR(15) NOT NULL,
    sexo ENUM('M','F') NOT NULL,
    dataNascimento DATE NOT NULL,
    nomeCompleto VARCHAR(100) NOT NULL,

    CONSTRAINT INTERNAUTA_PK PRIMARY KEY(apelido)
) ENGINE = InnoDB;

CREATE TABLE INTERESSE (
    idInteresse INT NOT NULL,
    privacidade ENUM('P','I') NOT NULL,
    nome VARCHAR(100) NOT NULL,

    CONSTRAINT INTERESSE_PK PRIMARY KEY(idInteresse)
) ENGINE = InnoDB AUTO_INCREMENT = 1;

CREATE TABLE email (
    apelidoInternauta VARCHAR(15) NOT NULL,
    email VARCHAR(100) NOT NULL,
    
    CONSTRAINT email_INTERNAUTA_FK FOREIGN KEY(apelidoInternauta)
      REFERENCES INTERNAUTA(apelido),
    CONSTRAINT email_UK UNIQUE (email)
) ENGINE = InnoDB;

CREATE TABLE relaciona (
    apelidoInternauta VARCHAR(15) NOT NULL,
    apelidoInternautaAmigo VARCHAR(15) NOT NULL,
    
    CONSTRAINT relaciona_INTERNAUTA_FK_1 FOREIGN KEY (apelidoInternauta)
      REFERENCES INTERNAUTA(apelido),
    CONSTRAINT relaciona_INTERNAUTA_FK_2 FOREIGN KEY (apelidoInternautaAmigo)
      REFERENCES INTERNAUTA(apelido),
    CONSTRAINT relaciona_UK UNIQUE (apelidoInternauta, apelidoInternautaAmigo)
) ENGINE = InnoDB;

CREATE TABLE tem (
    apelidoInternauta VARCHAR(15) NOT NULL,
    idInteresse INT NOT NULL,

    CONSTRAINT tem_INTERNAUTA_FK FOREIGN KEY(apelidoInternauta)
      REFERENCES INTERNAUTA(apelido),
    CONSTRAINT tem_INTERESSE_FK FOREIGN KEY(idInteresse)
      REFERENCES INTERESSE(idInteresse),
    CONSTRAINT tem_UK UNIQUE (idInteresse, apelidoInternauta)
) ENGINE = InnoDB;
