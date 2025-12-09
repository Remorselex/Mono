# PostgreSQL Learning Guide
## Учебный план для работы с базами данных PostgreSQL

### 📚 Содержание
1. [Основы PostgreSQL](#основы-postgresql)
2. [Установка и настройка](#установка-и-настройка)
3. [Базовые команды psql](#базовые-команды-psql)
4. [SQL основы](#sql-основы)
5. [Работа с данными](#работа-с-данными)
6. [Бэкап и восстановление](#бэкап-и-восстановление)
7. [Администрирование](#администрирование)
8. [Продвинутые темы](#продвинутые-темы)
9. [Практические задания](#практические-задания)
10. [Полезные ресурсы](#полезные-ресурсы)

---

## 🎯 Основы PostgreSQL

### Что такое PostgreSQL?
PostgreSQL — это мощная объектно-реляционная система управления базами данных (ORDBMS) с открытым исходным кодом.

**Ключевые особенности:**
- ACID-совместимость
- Поддержка JSON/JSONB
- Расширяемость
- Надежность
- Соответствие стандартам SQL

### Архитектура
```
┌─────────────────┐
│   Приложение    │
└─────────────────┘
         │
┌─────────────────┐
│  PostgreSQL     │
│  ┌─────────────┐│
│  │   Процесс   ││
│  │  postmaster ││
│  └─────────────┘│
│  ┌─────────────┐│
│  │   Базы      ││
│  │   данных    ││
│  └─────────────┘│
└─────────────────┘
```

---

## 🛠️ Установка и настройка

### Локальная установка (Ubuntu/Debian)
```bash
# Обновление пакетов
sudo apt update

# Установка PostgreSQL
sudo apt install postgresql postgresql-contrib

# Запуск службы
sudo systemctl start postgresql
sudo systemctl enable postgresql

# Проверка статуса
sudo systemctl status postgresql
```

### Docker установка
```bash
# Запуск PostgreSQL в контейнере
docker run --name postgres-db \
  -e POSTGRES_PASSWORD=mypassword \
  -e POSTGRES_DB=mydb \
  -p 5432:5432 \
  -d postgres:15

# Подключение к контейнеру
docker exec -it postgres-db psql -U postgres -d mydb
```

### Первоначальная настройка
```bash
# Переключение на пользователя postgres
sudo -u postgres psql

# Создание нового пользователя
CREATE USER myuser WITH PASSWORD 'mypassword';

# Создание базы данных
CREATE DATABASE mydb OWNER myuser;

# Предоставление прав
GRANT ALL PRIVILEGES ON DATABASE mydb TO myuser;
```

---

## 💻 Базовые команды psql

### Подключение к базе данных
```bash
# Локальное подключение
psql -U username -d database_name

# Удаленное подключение
psql -h hostname -p 5432 -U username -d database_name

# Подключение через Docker
docker exec -it container_name psql -U username -d database_name
```

### Основные мета-команды
```sql
-- Список баз данных
\l

-- Подключение к базе данных
\c database_name

-- Список таблиц
\dt

-- Описание таблицы
\d table_name

-- Список пользователей
\du

-- Список схем
\dn

-- Выход из psql
\q

-- Помощь
\?

-- Выполнение SQL файла
\i /path/to/file.sql

-- Вывод результата в файл
\o /path/to/output.txt
```

---

## 📊 SQL основы

### Создание таблиц
```sql
-- Создание простой таблицы
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Создание таблицы с внешними ключами
CREATE TABLE posts (
    id SERIAL PRIMARY KEY,
    title VARCHAR(200) NOT NULL,
    content TEXT,
    user_id INTEGER REFERENCES users(id) ON DELETE CASCADE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Создание индексов
CREATE INDEX idx_users_email ON users(email);
CREATE INDEX idx_posts_user_id ON posts(user_id);
```

### Типы данных PostgreSQL
```sql
-- Числовые типы
SMALLINT        -- 2 байта, -32768 до 32767
INTEGER         -- 4 байта, -2147483648 до 2147483647
BIGINT          -- 8 байт
DECIMAL(p,s)    -- точная арифметика
NUMERIC(p,s)    -- точная арифметика
REAL            -- 4 байта, переменная точность
DOUBLE PRECISION -- 8 байт, переменная точность
SERIAL          -- автоинкремент INTEGER
BIGSERIAL       -- автоинкремент BIGINT

-- Символьные типы
CHAR(n)         -- фиксированная длина
VARCHAR(n)      -- переменная длина с ограничением
TEXT            -- переменная длина без ограничения

-- Дата и время
DATE            -- дата (год, месяц, день)
TIME            -- время (час, минута, секунда)
TIMESTAMP       -- дата и время
TIMESTAMPTZ     -- дата и время с часовым поясом
INTERVAL        -- интервал времени

-- Логический тип
BOOLEAN         -- true/false/null

-- JSON типы
JSON            -- JSON данные (текст)
JSONB           -- JSON данные (бинарный формат)

-- Массивы
INTEGER[]       -- массив целых чисел
TEXT[]          -- массив строк

-- UUID
UUID            -- универсальный уникальный идентификатор
```

---

## 🔄 Работа с данными

### Вставка данных (INSERT)
```sql
-- Простая вставка
INSERT INTO users (username, email, password_hash) 
VALUES ('john_doe', 'john@example.com', 'hashed_password');

-- Множественная вставка
INSERT INTO users (username, email, password_hash) VALUES
    ('alice', 'alice@example.com', 'hash1'),
    ('bob', 'bob@example.com', 'hash2'),
    ('charlie', 'charlie@example.com', 'hash3');

-- Вставка с возвратом данных
INSERT INTO users (username, email, password_hash) 
VALUES ('dave', 'dave@example.com', 'hash4')
RETURNING id, username, created_at;

-- Вставка из другой таблицы
INSERT INTO archived_users (username, email)
SELECT username, email FROM users WHERE created_at < '2023-01-01';
```

### Выборка данных (SELECT)
```sql
-- Простая выборка
SELECT * FROM users;

-- Выборка определенных столбцов
SELECT username, email FROM users;

-- Выборка с условием
SELECT * FROM users WHERE created_at > '2024-01-01';

-- Выборка с сортировкой
SELECT * FROM users ORDER BY created_at DESC;

-- Выборка с ограничением
SELECT * FROM users LIMIT 10 OFFSET 20;

-- Выборка с группировкой
SELECT DATE(created_at) as date, COUNT(*) as user_count 
FROM users 
GROUP BY DATE(created_at)
ORDER BY date;

-- Выборка с соединениями
SELECT u.username, p.title, p.created_at
FROM users u
JOIN posts p ON u.id = p.user_id
WHERE u.created_at > '2024-01-01'
ORDER BY p.created_at DESC;
```

### Обновление данных (UPDATE)
```sql
-- Простое обновление
UPDATE users SET email = 'newemail@example.com' WHERE id = 1;

-- Обновление нескольких полей
UPDATE users 
SET email = 'updated@example.com', 
    updated_at = CURRENT_TIMESTAMP 
WHERE username = 'john_doe';

-- Обновление с подзапросом
UPDATE posts 
SET title = 'Updated: ' || title 
WHERE user_id IN (SELECT id FROM users WHERE created_at < '2023-01-01');
```

### Удаление данных (DELETE)
```sql
-- Простое удаление
DELETE FROM users WHERE id = 1;

-- Удаление с условием
DELETE FROM posts WHERE created_at < '2023-01-01';

-- Удаление с подзапросом
DELETE FROM posts 
WHERE user_id IN (SELECT id FROM users WHERE username LIKE 'test_%');
```

---

## 💾 Бэкап и восстановление

### pg_dump - создание бэкапов
```bash
# Полный бэкап базы данных
pg_dump -U username -d database_name > backup.sql

# Бэкап только данных
pg_dump -U username -d database_name --data-only > data_backup.sql

# Бэкап только структуры
pg_dump -U username -d database_name --schema-only > schema_backup.sql

# Бэкап в сжатом формате
pg_dump -U username -d database_name -Fc > backup.dump

# Бэкап конкретной таблицы
pg_dump -U username -d database_name -t table_name > table_backup.sql

# Бэкап с исключением таблиц
pg_dump -U username -d database_name --exclude-table=logs > backup_no_logs.sql

# Бэкап через Docker
docker exec container_name pg_dump -U username -d database_name > backup.sql
```

### pg_restore - восстановление
```bash
# Восстановление из SQL файла
psql -U username -d database_name < backup.sql

# Восстановление из сжатого формата
pg_restore -U username -d database_name backup.dump

# Восстановление с очисткой
pg_restore -U username -d database_name --clean backup.dump

# Восстановление только данных
pg_restore -U username -d database_name --data-only backup.dump

# Восстановление конкретной таблицы
pg_restore -U username -d database_name -t table_name backup.dump

# Восстановление через Docker
docker exec -i container_name psql -U username -d database_name < backup.sql
```

### Автоматизация бэкапов
```bash
#!/bin/bash
# backup_script.sh

DB_NAME="mydb"
DB_USER="myuser"
BACKUP_DIR="/backups"
DATE=$(date +%Y%m%d_%H%M%S)

# Создание директории
mkdir -p $BACKUP_DIR

# Создание бэкапа
pg_dump -U $DB_USER -d $DB_NAME > "$BACKUP_DIR/${DB_NAME}_${DATE}.sql"

# Удаление старых бэкапов (старше 7 дней)
find $BACKUP_DIR -name "*.sql" -mtime +7 -delete

echo "Backup completed: ${DB_NAME}_${DATE}.sql"
```

---

## ⚙️ Администрирование

### Управление пользователями
```sql
-- Создание пользователя
CREATE USER new_user WITH PASSWORD 'password';

-- Изменение пароля
ALTER USER username PASSWORD 'new_password';

-- Предоставление прав
GRANT SELECT, INSERT, UPDATE ON table_name TO username;
GRANT ALL PRIVILEGES ON DATABASE database_name TO username;

-- Отзыв прав
REVOKE INSERT, UPDATE ON table_name FROM username;

-- Удаление пользователя
DROP USER username;

-- Просмотр прав
\dp table_name
```

### Мониторинг и диагностика
```sql
-- Активные подключения
SELECT pid, usename, application_name, client_addr, state, query
FROM pg_stat_activity
WHERE state = 'active';

-- Размер баз данных
SELECT datname, pg_size_pretty(pg_database_size(datname)) as size
FROM pg_database
ORDER BY pg_database_size(datname) DESC;

-- Размер таблиц
SELECT schemaname, tablename, 
       pg_size_pretty(pg_total_relation_size(schemaname||'.'||tablename)) as size
FROM pg_tables
WHERE schemaname = 'public'
ORDER BY pg_total_relation_size(schemaname||'.'||tablename) DESC;

-- Статистика по таблицам
SELECT schemaname, tablename, n_tup_ins, n_tup_upd, n_tup_del
FROM pg_stat_user_tables;

-- Блокировки
SELECT blocked_locks.pid AS blocked_pid,
       blocked_activity.usename AS blocked_user,
       blocking_locks.pid AS blocking_pid,
       blocking_activity.usename AS blocking_user,
       blocked_activity.query AS blocked_statement
FROM pg_catalog.pg_locks blocked_locks
JOIN pg_catalog.pg_stat_activity blocked_activity ON blocked_activity.pid = blocked_locks.pid
JOIN pg_catalog.pg_locks blocking_locks ON blocking_locks.locktype = blocked_locks.locktype
JOIN pg_catalog.pg_stat_activity blocking_activity ON blocking_activity.pid = blocking_locks.pid
WHERE NOT blocked_locks.granted;
```

### Настройка производительности
```sql
-- Анализ медленных запросов
-- В postgresql.conf:
-- log_min_duration_statement = 1000  # логировать запросы > 1 сек
-- log_statement = 'all'              # логировать все запросы

-- Анализ плана выполнения
EXPLAIN ANALYZE SELECT * FROM users WHERE email = 'test@example.com';

-- Обновление статистики
ANALYZE table_name;

-- Полная очистка и анализ
VACUUM FULL ANALYZE table_name;
```

---

## 🚀 Продвинутые темы

### Работа с JSON
```sql
-- Создание таблицы с JSON
CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    attributes JSONB
);

-- Вставка JSON данных
INSERT INTO products (name, attributes) VALUES
    ('Laptop', '{"brand": "Dell", "ram": "16GB", "storage": "512GB SSD"}'),
    ('Phone', '{"brand": "Apple", "model": "iPhone 13", "color": "blue"}');

-- Запросы к JSON полям
SELECT name, attributes->>'brand' as brand FROM products;
SELECT * FROM products WHERE attributes->>'brand' = 'Dell';
SELECT * FROM products WHERE attributes @> '{"brand": "Apple"}';

-- Обновление JSON полей
UPDATE products 
SET attributes = attributes || '{"warranty": "2 years"}'
WHERE id = 1;
```

### Триггеры
```sql
-- Создание функции для триггера
CREATE OR REPLACE FUNCTION update_modified_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = CURRENT_TIMESTAMP;
    RETURN NEW;
END;
$$ language 'plpgsql';

-- Создание триггера
CREATE TRIGGER update_users_modtime 
    BEFORE UPDATE ON users 
    FOR EACH ROW 
    EXECUTE FUNCTION update_modified_column();
```

### Представления (Views)
```sql
-- Создание представления
CREATE VIEW user_posts AS
SELECT u.username, u.email, p.title, p.created_at
FROM users u
JOIN posts p ON u.id = p.user_id;

-- Использование представления
SELECT * FROM user_posts WHERE username = 'john_doe';

-- Материализованное представление
CREATE MATERIALIZED VIEW user_stats AS
SELECT u.username, COUNT(p.id) as post_count
FROM users u
LEFT JOIN posts p ON u.id = p.user_id
GROUP BY u.id, u.username;

-- Обновление материализованного представления
REFRESH MATERIALIZED VIEW user_stats;
```

### Транзакции
```sql
-- Начало транзакции
BEGIN;

-- Выполнение операций
INSERT INTO users (username, email, password_hash) 
VALUES ('test_user', 'test@example.com', 'hash');

UPDATE posts SET title = 'Updated title' WHERE id = 1;

-- Создание точки сохранения
SAVEPOINT my_savepoint;

DELETE FROM posts WHERE id = 2;

-- Откат к точке сохранения
ROLLBACK TO my_savepoint;

-- Подтверждение транзакции
COMMIT;

-- Или откат всей транзакции
-- ROLLBACK;
```

---

## 🎯 Практические задания

### Задание 1: Создание блога
```sql
-- 1. Создайте структуру для блога
CREATE TABLE categories (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) UNIQUE NOT NULL,
    description TEXT
);

CREATE TABLE authors (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    bio TEXT
);

CREATE TABLE articles (
    id SERIAL PRIMARY KEY,
    title VARCHAR(200) NOT NULL,
    content TEXT NOT NULL,
    author_id INTEGER REFERENCES authors(id),
    category_id INTEGER REFERENCES categories(id),
    published_at TIMESTAMP,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 2. Заполните тестовыми данными
INSERT INTO categories (name, description) VALUES
    ('Technology', 'Articles about technology'),
    ('Science', 'Scientific articles'),
    ('Programming', 'Programming tutorials and tips');

INSERT INTO authors (name, email, bio) VALUES
    ('John Smith', 'john@example.com', 'Tech writer'),
    ('Jane Doe', 'jane@example.com', 'Science journalist');

-- 3. Создайте запросы для:
-- - Получения всех статей с именами авторов и категорий
-- - Подсчета статей по категориям
-- - Поиска статей по ключевым словам в заголовке
```

### Задание 2: Система заказов
```sql
-- Создайте систему для интернет-магазина с таблицами:
-- customers, products, orders, order_items
-- Реализуйте запросы для получения статистики продаж
```

### Задание 3: Бэкап и восстановление
```bash
# 1. Создайте бэкап созданной базы данных
# 2. Удалите несколько записей
# 3. Восстановите данные из бэкапа
# 4. Создайте скрипт автоматического бэкапа
```

---

## 📚 Полезные ресурсы

### Официальная документация
- [PostgreSQL Documentation](https://www.postgresql.org/docs/) - Официальная документация
- [PostgreSQL Tutorial](https://www.postgresqltutorial.com/) - Подробные туториалы

### Книги
- **"PostgreSQL: Up and Running"** by Regina Obe, Leo Hsu
- **"Mastering PostgreSQL"** by Hans-Jürgen Schönig
- **"PostgreSQL High Performance"** by Gregory Smith

### Онлайн курсы
- [PostgreSQL на Coursera](https://www.coursera.org/learn/postgresql-database)
- [PostgreSQL на Udemy](https://www.udemy.com/topic/postgresql/)
- [PostgreSQL на Pluralsight](https://www.pluralsight.com/courses/postgresql-getting-started)

### Инструменты
- **pgAdmin** - Графический интерфейс для PostgreSQL
- **DBeaver** - Универсальный клиент баз данных
- **DataGrip** - IDE для баз данных от JetBrains
- **psql** - Командная строка PostgreSQL

### Полезные сайты
- [PostgreSQL Wiki](https://wiki.postgresql.org/)
- [Planet PostgreSQL](https://planet.postgresql.org/) - Блоги сообщества
- [PostgreSQL Weekly](https://postgresweekly.com/) - Еженедельная рассылка
- [Stack Overflow PostgreSQL](https://stackoverflow.com/questions/tagged/postgresql)

### Сообщества
- [PostgreSQL Slack](https://postgres-slack.herokuapp.com/)
- [Reddit r/PostgreSQL](https://www.reddit.com/r/PostgreSQL/)
- [PostgreSQL Telegram](https://t.me/postgresql_ru) - Русскоязычное сообщество

### Практические ресурсы
- [SQLBolt](https://sqlbolt.com/) - Интерактивные SQL упражнения
- [W3Schools SQL](https://www.w3schools.com/sql/) - Базовые SQL уроки
- [HackerRank SQL](https://www.hackerrank.com/domains/sql) - Задачи по SQL
- [LeetCode Database](https://leetcode.com/problemset/database/) - Алгоритмические задачи

---

## 📈 План изучения (8 недель)

### Неделя 1-2: Основы
- [ ] Установка и настройка PostgreSQL
- [ ] Изучение psql команд
- [ ] Создание первой базы данных
- [ ] Базовые типы данных

### Неделя 3-4: SQL запросы
- [ ] SELECT, INSERT, UPDATE, DELETE
- [ ] JOIN операции
- [ ] Группировка и агрегация
- [ ] Подзапросы

### Неделя 5-6: Администрирование
- [ ] Управление пользователями
- [ ] Бэкап и восстановление
- [ ] Мониторинг производительности
- [ ] Индексы и оптимизация

### Неделя 7-8: Продвинутые темы
- [ ] JSON/JSONB
- [ ] Триггеры и функции
- [ ] Представления
- [ ] Транзакции

---

## 🎓 Сертификация

### PostgreSQL Professional Certification
- **PGCP** - PostgreSQL Certified Professional
- **Сайт:** [PostgreSQL Professional](https://postgrespro.ru/education/certification)

### Альтернативные сертификации
- **Oracle Database SQL Certified Associate**
- **Microsoft SQL Server certifications**
- **MySQL certifications**

---

*Этот гид поможет вам освоить PostgreSQL от базового до продвинутого уровня. Начните с основ и постепенно переходите к более сложным темам. Удачи в изучении!*
