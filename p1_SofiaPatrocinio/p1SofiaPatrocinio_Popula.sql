-- --------     << Sofia Patrocínio >>     ------------
-- 
-- SCRIPT DE MANIPULAÇÃO (DML)
-- 
-- Data Criacao ...........: 06/04/2021
-- Autor(es) ..............: Sofia Costa Patrocínio
-- Banco de Dados .........: MySQL 8.0.23
-- Banco de Dados(nome) ...: SofiaPatrocinio
-- 
-- PROJETO => 01 Base de Dados
--         => 05 Tabelas
-- -----------------------------------------------------------------
USE SofiaPatrocinio;

INSERT INTO INTERNAUTA ( apelido, sexo, dataNascimento, nomeCompleto) VALUES('gpatrocinio', 'M', '1997-03-19', 'Guilherme Costa Patrocinio');
INSERT INTO INTERNAUTA ( apelido, sexo, dataNascimento, nomeCompleto) VALUES('sofiapatrocinio', 'F', '2000-01-03', 'Sofia Costa Patrocinio');
INSERT INTO INTERNAUTA ( apelido, sexo, dataNascimento, nomeCompleto) VALUES('mpatrocinio', 'M', '1995-10-31', 'Mateus Costa Patrocinio');
INSERT INTO INTERNAUTA ( apelido, sexo, dataNascimento, nomeCompleto) VALUES('aradipatrocinio', 'F', '1976-07-27', 'Arádia de Jesus Costa Patrocinio');

INSERT INTO INTERESSE (idInteresse, privacidade, nome) VALUES (1, 'P', 'Política');
INSERT INTO INTERESSE (idInteresse, privacidade, nome) VALUES (2, 'P', 'Futebol');

INSERT INTO email (apelidoInternauta, email) VALUES ('sofiapatrocinio', 'spsp@gmail.com');
INSERT INTO email (apelidoInternauta, email) VALUES ('gpatrocinio', 'guilherme@gmail.com');

INSERT INTO relaciona (apelidoInternauta, apelidoInternautaAmigo) VALUES ('gpatrocinio', 'sofiapatrocinio');
INSERT INTO relaciona (apelidoInternauta, apelidoInternautaAmigo) VALUES ('sofiapatrocinio', 'aradipatrocinio');

INSERT INTO tem (apelidoInternauta, idInteresse) VALUES ('sofiapatrocinio', 1);
INSERT INTO tem (apelidoInternauta, idInteresse) VALUES ('sofiapatrocinio', 2);
