/**************************************************
 * Title: DatabaseSystem - Project 2 Example
 * Summary: blah blah
 *  |Date              |Author             |Version
    |2024-12-31        |Gildong Hong       |1.0.0
**************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include < string.h >
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost"; // change if necessary
const char* user = "root";      // change if necessary
const char* pw = "ythan252731";       // change if necessary

#define MAX_LEN			999999

int main(void) {
    MYSQL* connection = NULL;
    MYSQL conn;
    MYSQL_RES* sql_result;
    MYSQL_ROW sql_row;
    FILE* fp = fopen("CRUD.txt", "rt");    // open CRUD file.
    char line[MAX_LEN];
    int cnt6 = 0;

    if (mysql_init(&conn) == NULL)
        printf("mysql_init() error!");

    connection = mysql_real_connect(&conn, host, user, pw, NULL, 3306, (const char*)NULL, 0);   // the first NULL can be replaced to an existing db instance.
    if (connection == NULL) {
        printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
        return 1;
    }
    else {
        printf("Connection Succeed\n\n");

        // read CRUD file
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (!strcmp(line, "$$$\n"))      // read lines from CRUD file, '$$$' separates CREATE / DELETE parts.
                break;
            mysql_query(connection, line);
        }

        if (mysql_select_db(&conn, "project")) {
            printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 1;
        }

        //If connection is succeeded, run the program
        int q_type, sub_type, i;
        int state = 0;;
        while (1) {
            //Type Selection Menu
            printf("---------- SELECT QUERY TYPES ----------\n\n");
            for (i = 1; i < 8; i++) {
                printf("\t%d. TYPE %d\n", i, i);
            }
            printf("\t0. QUIT\n\nEnter the number of TYPE: ");
            scanf("%d", &q_type);

            //if the input is 0 -> break the loop
            if (q_type == 0) {
                break;
            }

            //if the input is 1 -> run the query of TYPE 1
            else if (q_type == 1) {
                const char* query1 = "SELECT detailed_address FROM properties WHERE properties.ID NOT IN(SELECT property_ID FROM contract) AND properties.district = 'Mapo'; ";
                state = 0;
                state = mysql_query(connection, query1);
                if (state == 0) {
                    sql_result = mysql_store_result(connection);

                    //Print the result of TYPE 1-1
                    printf("\nTYPE 1: Find the address of homes for sale in the district \"Mapo\".\n\n");
                    printf("\tAddress\n");
                    while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                        printf("\t%s\n", sql_row[0]);
                    printf("\n");
                    mysql_free_result(sql_result);
                }
                else {
                    //Query Error Message
                    fprintf(stderr, "query error: %s\n", mysql_error(connection));
                    mysql_close(connection);
                }

                //Subtypes of TYPE 1
                while(1) {
                //SUBTYPE Selection Menu
                printf("---------- Subtype in TYPES 1 ----------\n");
                printf("\t1. TYPE 1-1\n\n");
                printf("Enter a number of subtype or enter \"0\" to go back to the TYPE Selection menu: ");
                scanf("%d", &sub_type);
                printf("\n");

                //if the input is 0 -> go back to TYPE Selection Menu
                if (sub_type == 0) {
                    break;
                }
                //if the input is 1 -> run the query of TYPE 1-1
                else if (sub_type == 1) {
                    const char* query1_1 = "SELECT properties.ID, detailed_address, price FROM multiroom_and_detached LEFT JOIN properties ON multiroom_and_detached.ID = properties.ID WHERE multiroom_and_detached.ID IN(SELECT ID FROM properties WHERE properties.ID NOT IN(SELECT property_ID FROM contract) AND properties.district = 'Mapo') AND multiroom_and_detached.price <= 1500000000 AND multiroom_and_detached.price >= 1000000000; ";
                    state = 0;
                    state = mysql_query(connection, query1_1);
                    if (state == 0) {
                        sql_result = mysql_store_result(connection);

                        //Print the result of TYPE 1-1
                        printf("TYPE 1-1: Then find the costing between £Ü1,000,000,000 and £Ü1,500,000,000.\n\n");
                        printf("\t%-15s\t%-15s\t%-15s\n", "Properties ID", "Address", "Price");
                        while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                            printf("\t%s\t%s\t\%s\n", sql_row[0], sql_row[1], sql_row[2]);
                        mysql_free_result(sql_result);
                    }
                    else {
                        //Query Error Message
                        fprintf(stderr, "query error: %s\n", mysql_error(connection));
                        mysql_close(connection);
                    }

                    const char* query1_2 = "SELECT properties.ID, detailed_address, price FROM studio_and_oneroom LEFT JOIN properties ON studio_and_oneroom.ID = properties.ID WHERE studio_and_oneroom.ID IN(SELECT ID FROM properties WHERE properties.ID NOT IN(SELECT property_ID FROM contract) AND properties.district = 'Mapo') AND studio_and_oneroom.price <= 1500000000 AND studio_and_oneroom.price >= 1000000000; ";
                    state = 0;
                    state = mysql_query(connection, query1_2);
                    if (state == 0) {
                        sql_result = mysql_store_result(connection);

                        while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                            printf("\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2]);
                        mysql_free_result(sql_result);
                        printf("\n\n");
                    }
                    else {
                        //Query Error Message
                        fprintf(stderr, "query error: %s\n", mysql_error(connection));
                        mysql_close(connection);
                    }
                }
                else {
                    //Instruction Message for wrong input
                    printf("You entered a wrong number. Available numbers are 0 and 1.\n\n");
                }
                }
            }
            //if the input is 2 -> run the query of TYPE 2
            else if (q_type == 2) {
                const char* query2 = "SELECT p.ID, p.district, p.detailed_address, s.school_district FROM properties p LEFT JOIN school_dist s ON p.district = s.district WHERE p.ID NOT IN(SELECT property_ID FROM contract) AND s.school_district = 8; ";
                state = 0;
                state = mysql_query(connection, query2);
                if (state == 0) {
                    sql_result = mysql_store_result(connection);

                    //Print the result of TYPE 2
                    printf("\nTYPE 2: Find the address of homes for sale in the 8th shcool district.\n\n");
                    printf("\t%-15s\t%-15s\t%-15s\t%-15s\n", "Properties ID", "District", "Address", "School district");
                    while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                        printf("\t%-15s\t%-15s\t%-15s\t%-15s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
                    printf("\n");
                    mysql_free_result(sql_result);
                }
                else {
                    //Query Error Message
                    fprintf(stderr, "query error: %s\n", mysql_error(connection));
                    mysql_close(connection);
                }

                //Subtypes of TYPE 2
                while (1) {
                    //SUBTYPE Selection Menu
                    printf("---------- Subtype in TYPES 2 ----------\n");
                    printf("\t1. TYPE 2-1\n\n");
                    printf("Enter a number of subtype or enter \"0\" to go back to the TYPE Selection menu: ");
                    scanf("%d", &sub_type);
                    printf("\n");

                    //if the input is 0 -> go back to TYPE Selection Menu
                    if (sub_type == 0) {
                        break;
                    }
                    else if (sub_type==1) {
                        const char* query2_1 = "SELECT p.ID, p.detailed_address, s.school_district, p.num_of_bedroom, p.num_of_bathroom FROM properties p LEFT JOIN school_dist s ON p.district = s.district WHERE p.ID NOT IN(SELECT property_ID FROM contract) AND s.school_district = 8 AND p.num_of_bedroom >= 4  AND p.num_of_bathroom = 2;";
                        state = 0;
                        state = mysql_query(connection, query2_1);
                        if (state == 0) {
                            sql_result = mysql_store_result(connection);

                            //Print the result of TYPE 2-1
                            printf("\nTYPE 2-1: Then find properties with 4 or more bedrooms and 2 bathrooms.\n\n");
                            printf("\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", "Properties ID", "Address", "School district", "# of bedroom", "# of bathroom");
                            while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                                printf("\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
                            printf("\n");
                            mysql_free_result(sql_result);
                        }
                        else {
                            //Query Error Message
                            fprintf(stderr, "query error: %s\n", mysql_error(connection));
                            mysql_close(connection);
                        }
                    }
                    else {
                        //Instruction Message for wrong input
                        printf("You entered a wrong number. Available numbers are 0 and 1.\n\n");
                    }
                }
            }
            //if the input is 3 -> run the query of TYPE 3
            else if (q_type == 3) {
                const char* query3 = "SELECT c.sellers_agent_ID, a.first_name, a.last_name, SUM(IFNULL(s.Price, 0) + IFNULL(m.Price, 0)) AS total_price_sum FROM contract c LEFT JOIN(SELECT ID, Price FROM studio_and_oneroom) s ON c.property_ID = s.ID LEFT JOIN(SELECT ID, Price FROM multiroom_and_detached) m ON c.property_ID = m.ID LEFT JOIN(SELECT ID, first_name, last_name FROM agent) a ON c.sellers_agent_ID = a.ID WHERE YEAR(c.contract_date) = 2022 GROUP BY c.sellers_agent_ID ORDER BY total_price_sum DESC LIMIT 1; ";
                state = 0;
                state = mysql_query(connection, query3);
                if (state == 0) {
                    sql_result = mysql_store_result(connection);

                    //Print the result of TYPE 3
                    printf("\nTYPE 3: Find the name of the agent who has sold the most properties in the year 2022 by total won value.\n\n");
                    printf("\t%-15s\t%-15s\t%-15s\n", "Agent ID", "Name", "Total Price");
                    while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                        printf("\t%-15s\t%-7s%-8s\t%-15s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
                    printf("\n");
                    mysql_free_result(sql_result);
                }
                else {
                    //Query Error Message
                    fprintf(stderr, "query error: %s\n", mysql_error(connection));
                    mysql_close(connection);
                }

                //Subtypes of TYPE 3
                while (1) {
                    //SUBTYPE Selection Menu
                    printf("---------- Subtype in TYPES 3 ----------\n");
                    printf("\t1. TYPE 3-1\n");
                    printf("\t2. TYPE 3-2\n\n");
                    printf("Enter a number of subtype or enter \"0\" to go back to the TYPE Selection menu: ");
                    scanf("%d", &sub_type);
                    printf("\n");

                    //if the input is 0 -> go back to TYPE Selection Menu
                    if (sub_type == 0) {
                        break;
                    }
                    else if (sub_type == 1) {
                        int k;
                        char strk[100];

                        printf("---------- TYPES 3-1 ----------\n\n");
                        printf("** Then find the top k agents in the year 2023 by total won value. **\n");
                        printf(" (if the number of agent under condition(n) is less than K, n tuples will be shown)\n");
                        printf(" Which K? : ");
                        scanf("%d", &k);
                        sprintf(strk, "%d", k); //trans int into char array

                        char query3_1[999];
                        const char* query3_1_1 = "SELECT c.sellers_agent_ID, a.first_name, a.last_name, SUM(IFNULL(s.Price, 0) + IFNULL(m.Price, 0)) AS total_price_sum FROM contract c LEFT JOIN(SELECT ID, Price FROM studio_and_oneroom) s ON c.property_ID = s.ID LEFT JOIN(SELECT ID, Price FROM multiroom_and_detached) m ON c.property_ID = m.ID LEFT JOIN(SELECT ID, first_name, last_name FROM agent) a ON c.sellers_agent_ID = a.ID WHERE YEAR(c.contract_date) = 2023 GROUP BY c.sellers_agent_ID ORDER BY total_price_sum DESC LIMIT ";
                        strcpy(query3_1, query3_1_1);
                        strcat(query3_1, strk);
                        state = 0;
                        state = mysql_query(connection, query3_1);
                        if (state == 0) {
                            sql_result = mysql_store_result(connection);

                            //Print the result of TYPE 3-1
                            printf("\nTYPE 3-1: Then find the top k agents in the year 2023 by total won value.\n\n");
                            printf("\t%-15s\t%-20s\t%-15s\n", "Agent ID", "Name", "Total Price");
                            while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                                printf("\t%-15s\t%-10s%-10s\t%-15s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
                            printf("\n");
                            mysql_free_result(sql_result);
                        }
                        else {
                            //Query Error Message
                            fprintf(stderr, "query error: %s\n", mysql_error(connection));
                            mysql_close(connection);
                        }
                    }
                    else if (sub_type == 2) {
                        const char* query3_2 = "SELECT main.sellers_agent_ID, main.first_name, main.last_name, main.total_price_sum FROM (SELECT c.sellers_agent_ID, a.first_name, a.last_name, SUM(IFNULL(s.Price, 0) + IFNULL(m.Price, 0)) AS total_price_sum, ROW_NUMBER() OVER (ORDER BY SUM(IFNULL(s.Price, 0) + IFNULL(m.Price, 0)) ASC) AS row_num FROM contract c LEFT JOIN studio_and_oneroom s ON c.property_ID = s.ID LEFT JOIN multiroom_and_detached m ON c.property_ID = m.ID LEFT JOIN agent a ON c.sellers_agent_ID = a.ID WHERE YEAR(c.contract_date) = 2021 GROUP BY c.sellers_agent_ID, a.first_name, a.last_name) AS main WHERE main.row_num <= (SELECT FLOOR(COUNT(DISTINCT sellers_agent_ID) / 10) FROM contract WHERE YEAR(contract_date) = 2021);";
                        state = 0;
                        state = mysql_query(connection, query3_2);
                        if (state == 0) {
                            sql_result = mysql_store_result(connection);

                            //Print the result of TYPE 3-2
                            printf("\nTYPE 3-2: And then find the bottom 10% agents in the year 2021 by total won value.\n\n");
                            printf("\t%-15s\t%-20s\t%-15s\n", "Agent ID", "Name", "Total Price");
                            while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                                printf("\t%-15s\t%-10s%-10s\t%-15s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
                            printf("\n");
                            mysql_free_result(sql_result);
                        }
                        else {
                            //Query Error Message
                            fprintf(stderr, "query error: %s\n", mysql_error(connection));
                            mysql_close(connection);
                        }
                    }
                    else {
                        //Instruction Message for wrong input
                        printf("You entered a wrong number. Available numbers are between 0 to 2.\n\n");
                    }
                }
            }
            //if the input is 4 -> run the query of TYPE 4
            else if (q_type == 4) {
                const char* query4 = "SELECT c.sellers_agent_ID, AVG(s.price) AS avg_price, AVG(DATEDIFF(c.contract_date, s.registered_date)) AS avg_time_on_market FROM contract c LEFT JOIN studio_and_oneroom s ON c.property_ID = s.ID WHERE YEAR(c.contract_date) = 2022 GROUP BY c.sellers_agent_ID; ";
                state = 0;
                state = mysql_query(connection, query4);
                if (state == 0) {
                    sql_result = mysql_store_result(connection);

                    //Print the result of TYPE 4
                    printf("\nTYPE 4: For each agent, compute the average selling price of properties sold in 2022, and the average time the property was on the market.\n\n");
                    printf("\t%-15s\t%-20s\t%-20s\n", "Agent ID", "avg Price", "avg time on market(days)");
                    while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                        printf("\t%-15s\t%-20s\t%-15s\n", sql_row[0], sql_row[1], sql_row[2]);
                    printf("\n");
                    mysql_free_result(sql_result);
                }
                else {
                    //Query Error Message
                    fprintf(stderr, "query error: %s\n", mysql_error(connection));
                    mysql_close(connection);
                }

                //Subtypes of TYPE 4
                while (1) {
                    //SUBTYPE Selection Menu
                    printf("---------- Subtype in TYPES 4 ----------\n");
                    printf("\t1. TYPE 4-1\n");
                    printf("\t2. TYPE 4-2\n\n");
                    printf("Enter a number of subtype or enter \"0\" to go back to the TYPE Selection menu: ");
                    scanf("%d", &sub_type);
                    printf("\n");

                    //if the input is 0 -> go back to TYPE Selection Menu
                    if (sub_type == 0) {
                        break;
                    }
                    else if (sub_type == 1) {
                        const char* query4_1 = "SELECT c.sellers_agent_ID, MAX(s.price) AS max_price FROM contract c LEFT JOIN studio_and_oneroom s ON c.property_ID = s.ID WHERE YEAR(c.contract_date) = 2023 GROUP BY c.sellers_agent_ID;";
                        state = 0;
                        state = mysql_query(connection, query4_1);
                        if (state == 0) {
                            sql_result = mysql_store_result(connection);

                            //Print the result of TYPE 4-1
                            printf("\nTYPE 4-1: Then compute the maximum selling price of properties sold in 2023 for each agent.\n\n");
                            printf("\t%-15s\t%-15s\n", "Agent ID", "Max. Price");
                            while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                                printf("\t%-15s\t%-15s\n", sql_row[0], sql_row[1]);
                            printf("\n");
                            mysql_free_result(sql_result);
                        }
                        else {
                            //Query Error Message
                            fprintf(stderr, "query error: %s\n", mysql_error(connection));
                            mysql_close(connection);
                        }
                    }
                    else if (sub_type == 2) {
                        const char* query4_2 = "SELECT c.sellers_agent_ID, MAX(DATEDIFF(c.contract_date, s.registered_date)) AS max_time_on_market FROM contract c LEFT JOIN studio_and_oneroom s ON c.property_ID = s.ID GROUP BY c.sellers_agent_ID; ";
                        state = 0;
                        state = mysql_query(connection, query4_2);
                        if (state == 0) {
                            sql_result = mysql_store_result(connection);

                            //Print the result of TYPE 4-2
                            printf("\nTYPE 4-2: And then compute the longest time the property was on the market for each agent.\n\n");
                            printf("\t%-15s\t%-15s\n", "Agent ID", "Max. Time(days)");
                            while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                                printf("\t%-15s\t%-15s\n", sql_row[0], sql_row[1]);
                            printf("\n");
                            mysql_free_result(sql_result);
                        }
                        else {
                            //Query Error Message
                            fprintf(stderr, "query error: %s\n", mysql_error(connection));
                            mysql_close(connection);
                        }
                    }
                    else {
                        //Instruction Message for wrong input
                        printf("You entered a wrong number. Available numbers are between 0 to 2.\n\n");
                    }
                }
            }
            //if the input is 5 -> run the query of TYPE 5
            else if (q_type == 5) {
                const char* query5 = "(SELECT ID, interior_pic, outerior_pic, floor_plan FROM (SELECT ID, interior_pic, outerior_pic, floor_plan FROM studio_and_oneroom WHERE type_of_property = 0 ORDER BY price DESC LIMIT 1) AS t1) UNION (SELECT ID, interior_pic, outerior_pic, floor_plan FROM (SELECT ID, interior_pic, outerior_pic, floor_plan FROM studio_and_oneroom WHERE type_of_property = 1 ORDER BY price DESC LIMIT 1) AS t2) UNION (SELECT ID, interior_pic, outerior_pic, floor_plan FROM (SELECT ID, interior_pic, outerior_pic, floor_plan FROM multiroom_and_detached WHERE type_of_property = 2 ORDER BY price DESC LIMIT 1) AS t3) UNION (SELECT ID, interior_pic, outerior_pic, floor_plan FROM (SELECT ID, interior_pic, outerior_pic, floor_plan FROM multiroom_and_detached WHERE type_of_property = 3 ORDER BY price DESC LIMIT 1) AS t4);";
                state = 0;
                state = mysql_query(connection, query5);
                if (state == 0) {
                    sql_result = mysql_store_result(connection);

                    //Print the result of TYPE 5
                    char prop_types[][20] = {"Studio", "Oneroom", "Multiroom", "Detached house"};
                    int cnt = 0;
                    printf("\nTYPE 5: Showphotos of the most expensive studio, one - bedroom, multi - bedroom apartment(s), and detached house(s), respectively, from the database.\n\n");
                    printf("\t%-15s\t%-15s\t%-30s\t%-30s\t%-30s\n", "Property Type", "Property ID", "Interior pic", "Outerior pic", "Floor plan");
                    while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                        printf("\t%-15s\t%-15s\t%-30s\t%-30s\t%-30s\n", prop_types[cnt], sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
                        cnt += 1;
                    }
                    printf("\n");
                    printf("**images are replaced with \"just string\"\n\n");
                    mysql_free_result(sql_result);
                }
                else {
                    //Query Error Message
                    fprintf(stderr, "query error: %s\n", mysql_error(connection));
                    mysql_close(connection);
                }
            }
            //if the input is 6 -> run the query of TYPE 6
            else if (q_type == 6) {
                while (1) {
                    int back;
                    char cdate[10];
                    int buyer;
                    char cid[][11] = {"210-937992", "932-394010", "100-037808", "021-492611", "391-301911"};
                    char properties[][11] = {"41-52-6200", "58-06-2199", "55-76-8198", "26-25-1197", "88-61-5196"};
                    char seller[][14] = {"010-1562-3200", "010-5844-0199", "010-8033-0198", "010-2761-2197", "010-0043-8196"};
                    char sagent[][11] = {"0000-00624", "0000-00601", "0000-00868", "0000-00544", "0000-00794"};
                    char bagent[][11] = { "0000-00564", "0000-00562", "0000-00880", "0000-00614", "0000-00659" };
                    char buyers[][14] = { "010-2476-2301", "010-7673-0302", "010-3082-2303", "010-6835-2304", "010-3351-1305" };

                    printf("\nTYPE 6: Record the sale of a property that had been listed as being available.This entails storing the sales price, the buyer, the selling agent, the buyer¡¯s agent(if any), and the date. \n\n");

                    if (cnt6 == 5) {
                        printf("No properties available to contract anymore.\n\n");
                        break;
                    }

                    printf("Buyer candidates:\n 1) 010-2476-2301\n 2) 010-7673-0302\n 3) 010-3082-2303\n 4) 010-6835-2304\n 5) 010-3351-1305\n\n");
                    printf("Enter a buyer among buyer candidates (enter between 1 to 5): ");
                    scanf("%d", &buyer);
                    printf("Enter contract date (format: YYYY-MM-DD): ");
                    scanf("%s", &cdate);
                    printf("\n");

                    
                    char query6[300];
                    const char* query6_1 = "INSERT INTO contract Values (\'";
                    strcpy(query6, query6_1);
                    strcat(query6, cid[cnt6]);
                    strcat(query6, "\', \'");
                    strcat(query6, cdate);
                    strcat(query6, "\', \'");
                    strcat(query6, seller[cnt6]);
                    strcat(query6, "\', \'");
                    strcat(query6, sagent[cnt6]);
                    strcat(query6, "\', \'");
                    strcat(query6, buyers[buyer]);
                    strcat(query6, "\', \'");
                    strcat(query6, bagent[buyer]);
                    strcat(query6, "\', \'");
                    strcat(query6, properties[cnt6]);
                    strcat(query6, "\')");
                    
                    state = 0;
                    state = mysql_query(connection, query6);
                    if (state == 0) {
                        sql_result = mysql_store_result(connection);
                        printf("A new contract is recorded to the DB successfully.\n\n");
                        mysql_free_result(sql_result);
                        cnt6 += 1;
                    }
                    else {
                        //Error message
                        printf("The contract is not recorded. Please try again or restart the program.\n\n");
                        mysql_close(connection);
                    }

                    printf("If you want to go back to the TYPE Selection Menu, enter \"0\", otherwise enter any other number: ");
                    scanf("%d", &back);
                    printf("\n");
                    if (back == 0) {
                        break;
                    }
                }
            }
            //if the input is 7 -> run the query of TYPE 7
            else if (q_type == 7) {
                while (1) {
                    int back;
                    char agent[10];
                    char first[100];
                    char last[100];

                    printf("\nTYPE 7: Add a new agent to the database.\n\n");

                    printf("Enter agent ID (Format: 0000-00000): ");
                    scanf("%s", &agent);
                    printf("Enter agent's first name: ");
                    scanf("%s", &first);
                    printf("Enter agent's last name: ");
                    scanf("%s", &last);
                    printf("\n");

                    char query7[100];
                    const char* query7_1 = "INSERT INTO agent Values (\'";

                    strcpy(query7, query7_1);
                    strcat(query7, agent);
                    strcat(query7, "\', \'");
                    strcat(query7, first);
                    strcat(query7, "\', NULL, \'");
                    strcat(query7, last);
                    strcat(query7, "\', NULL)");

                    state = 0;
                    state = mysql_query(connection, query7);
                    if (state == 0) {
                        sql_result = mysql_store_result(connection);
                        printf("A new agent is added to the DB successfully.\n\n");

                        mysql_free_result(sql_result);
                    }
                    else {
                        //ID duplication message
                        printf("The input agent ID is already in the database. Please try other IDs.\n\n");
                        mysql_close(connection);
                    }

                    printf("If you want to go back to the TYPE Selection Menu, enter \"0\", otherwise enter any other number: ");
                    scanf("%d", &back);
                    printf("\n");
                    if (back == 0) {
                        break;
                    }
                }
            }
            else {
                //Instruction Message for wrong input
                printf("You entered a wrong number. Available numbers are between 0 to 7.\n\n");
                fprintf(stderr, "query error: %s\n", mysql_error(connection));
                mysql_close(connection);
            }
            
        }

        // comment out if you want to persist example db instance.
        while (fgets(line, sizeof(line), fp) != NULL)
            mysql_query(connection, line);			// these are DELETEs & DROPs.

        mysql_close(connection);
    }

    return 0;
}
