-- Keep a log of any SQL queries you execute as you solve the mystery.
--Figuring out the description
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 and year = 2021 AND street = "Humphrey Street"
--decoding the transcript
SELECT transcript from interviews where year = 2021 AND month = 7 AND day = 28;

--checking the license_plate who went with theft time frame
SELECT license_plate from bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25;

--checking account number
SELECT account_number, amount from atm_transactions where year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

--checking out the time from of callers
SELECT caller FROM phone_calls where year=2021 AND month = 7 AND day = 28 AND duration < 60;

--getting person id from atm transaction
SELECT person_id from bank_accounts WHERE account_number IN(SELECT account_number from atm_transactions where year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street" AND transaction_type = "withdraw")

--finding the common id for license plate and and account number
SELECT id from people WHERE license_plate IN(SELECT license_plate from bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25) AND id IN(SELECT person_id from bank_accounts WHERE account_number IN(SELECT account_number from atm_transactions where year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"));

--finding people id from phone number called during theft
SELECT id from people where phone_number IN(SELECT caller FROM phone_calls where year=2021 AND month = 7 AND day = 28 AND duration < 60);

--f0und the two suspects which where present during theft
SELECT name, passport_number from people WHERE id = 514354 OR id= 686048;

--getting flight id
select * from passengers where passport_number =  5773159633;

-- finding the culprit bruce
 select * from flights  where month = 7 AND year = 2021 AND day = 29 AND id = 36;

--finding the  by checking caller log
SELECT caller FROM phone_calls where year=2021 AND month = 7 AND day = 28 AND duration < 60;

--found the airport from airport table