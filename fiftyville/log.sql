SELECT description
FROM crime_scene_reports
WHERE month = 7
AND day = 28;

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at
-- the time – each of their interview transcripts mentions the bakery.

SELECT name, transcript
FROM interviews
WHERE month = 7
AND day = 28;

-- | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking
-- lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars
-- that left the parking lot in that time frame.

-- | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning,
-- before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief
-- there withdrawing some money.

-- | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less
-- than a minute. In the call, I heard the thief say that they were planning to take the earliest
-- flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone
-- to purchase the flight ticket.

SELECT *
FROM people
WHERE id IN
(
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
    (
        SELECT account_number
        FROM atm_transactions
        WHERE month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
);
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+

-- People who have withdraw transactions in 2023/07/28 at Leggett Street

SELECT people.name AS caller_name,
(
    SELECT name
    FROM people
    WHERE phone_number = phone_calls.receiver
)
AS receiver_name,
phone_calls.caller AS caller_number,
phone_calls.receiver AS receiver_number,
phone_calls.month,
phone_calls.day,
phone_calls.duration
FROM phone_calls
JOIN people
ON people.phone_number = phone_calls.caller
WHERE caller IN
(
    SELECT phone_number
    FROM people
    WHERE id IN
    (
        SELECT id
        FROM people
        WHERE id IN
        (
            SELECT person_id
            FROM bank_accounts
            WHERE account_number IN
            (
                SELECT account_number
                FROM atm_transactions
                WHERE month = 7
                AND day = 28
                AND atm_location = 'Leggett Street'
                AND transaction_type = 'withdraw'
            )
        )
    )
)
AND month = 7
AND day = 28
AND duration <= 60;
-- +-------------+---------------+----------------+-----------------+-------+-----+----------+
-- | caller_name | receiver_name | caller_number  | receiver_number | month | day | duration |
-- +-------------+---------------+----------------+-----------------+-------+-----+----------+
-- | Bruce       | Robin         | (367) 555-5533 | (375) 555-8161  | 7     | 28  | 45       |
-- | Taylor      | James         | (286) 555-6063 | (676) 555-6554  | 7     | 28  | 43       |
-- | Diana       | Philip        | (770) 555-1861 | (725) 555-3243  | 7     | 28  | 49       |
-- | Kenny       | Doris         | (826) 555-1652 | (066) 555-9701  | 7     | 28  | 55       |
-- | Benista     | Anna          | (338) 555-6650 | (704) 555-2131  | 7     | 28  | 54       |
-- +-------------+---------------+----------------+-----------------+-------+-----+----------+

-- Calls made in 2023/07/28 with less than 1min from people who have withdraw transactions in 2023/07/28 at
-- Leggett Street.

SELECT people.name,
people.license_plate,
people.passport_number,
(
    SELECT account_number
    FROM bank_accounts
    WHERE person_id = people.id
)
AS account_number,
bakery_security_logs.activity,
bakery_security_logs.month,
bakery_security_logs.day,
bakery_security_logs.hour,
bakery_security_logs.minute
FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
WHERE people.id IN
(
    SELECT people.id
    FROM people
    JOIN phone_calls
    ON people.phone_number = phone_calls.caller
    WHERE caller IN
    (
        SELECT phone_number
        FROM people
        WHERE id IN
        (
            SELECT id
            FROM people
            WHERE id IN
            (
                SELECT person_id
                FROM bank_accounts
                WHERE account_number IN
                (
                    SELECT account_number
                    FROM atm_transactions
                    WHERE month = 7
                    AND day = 28
                    AND atm_location = 'Leggett Street'
                    AND transaction_type = 'withdraw'
                )
            )
        )
    )
    AND month = 7
    AND day = 28
    AND duration <= 60
)
AND month = 7
AND day = 28
AND hour = 10
AND minute <= 25;

-- +-------+---------------+-----------------+----------------+----------+-------+-----+------+--------+
-- | name  | license_plate | passport_number | account_number | activity | month | day | hour | minute |
-- +-------+---------------+-----------------+----------------+----------+-------+-----+------+--------+
-- | Diana | 322W7JE       | 3592750733      | 26013199       | exit     | 7     | 28  | 10   | 23     |
-- | Bruce | 94KL13X       | 5773159633      | 49610011       | exit     | 7     | 28  | 10   | 18     |
-- +-------+---------------+-----------------+----------------+----------+-------+-----+------+--------+

-- Bakery security logs of 2023/07/28 from people that have calls made in 2023/07/28 with less than 1min
-- and have withdraw transactions in 2023/07/28 at Leggett Street.
-- Considered max of 10 minutes to leave the bakery (10:25am).


SELECT *
FROM flights
WHERE id IN
(
    SELECT flight_id
    FROM passengers
    WHERE passport_number =
    (
        SELECT passport_number FROM people WHERE name = 'Diana'
    )
)
AND month = 7
AND day = 29;

-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 18 | 8                 | 6                      | 2023 | 7     | 29  | 16   | 0      |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

-- All flights Diana did in 2023/07/09

SELECT *
FROM flights
WHERE id IN
(
    SELECT flight_id
    FROM passengers
    WHERE passport_number =
    (
        SELECT passport_number FROM people WHERE name = 'Bruce'
    )
)
AND month = 7
AND day = 29;
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

-- All flight Bruce did in 2023/07/09


SELECT *
FROM flights
WHERE month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1;

-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

-- The earliest flight in 2023/07/09
-- The flight Bruce took.
-- Robin bought the ticket.

SELECT
(
    SELECT full_name FROM airports WHERE id = 8
)
AS origin_airport_name,
(
    SELECT full_name FROM airports WHERE id = 4
)
AS destination_airport_name,
(
    SELECT city FROM airports WHERE id = 8
)
AS origin_city,
(
    SELECT city FROM airports WHERE id = 4
)
AS destination_city;

-- +-----------------------------+--------------------------+-------------+------------------+
-- |     origin_airport_name     | destination_airport_name | origin_city | destination_city |
-- +-----------------------------+--------------------------+-------------+------------------+
-- | Fiftyville Regional Airport | LaGuardia Airport        | Fiftyville  | New York City    |
-- +-----------------------------+--------------------------+-------------+------------------+

-- Bruce's origin and destination.

-- CONCLUSION:
-- Bruce is the THIEF;
-- Robin is the ACCOMPLICE
-- The city Bruce escaped to is New York City.
