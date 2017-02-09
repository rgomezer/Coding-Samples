ACCEPT p_1 PROMPT 'Please enter a positive integer:'
DECLARE
  v_rank_input   NUMBER := &p_1;  
  v_rank         popular_names.rank%TYPE;
  v_sex          popular_names.sex%TYPE;
  v_temp_sex         varchar2(10);
  v_name         popular_names.given_name%TYPE;
  v_number       popular_names.number_of_occurrences%TYPE;
  CURSOR c_name IS
        SELECT   	rank, sex, given_name, number_of_occurrences
        FROM 	  	popular_names        
        ORDER BY 	given_name;
BEGIN
  IF v_rank_input <= 0 THEN
    DBMS_OUTPUT.PUT_LINE('Invalid number: ' || TO_CHAR(v_rank_input));
  ELSE
    OPEN c_name;
    FETCH	c_name INTO v_rank, v_sex, v_name, v_number;
    IF c_name%NOTFOUND THEN
      DBMS_OUTPUT.PUT_LINE('Cannot find result.');
    ELSE
      DBMS_OUTPUT.PUT_LINE(RPAD('Given Name', 20) || RPAD('Rank', 7) || RPAD('Sex', 10) || 'Number of Occurrences');
      DBMS_OUTPUT.PUT_LINE(LPAD('=', 58, '='));
      LOOP
        IF v_rank <= v_rank_input THEN
          IF UPPER(v_sex) = 'M' THEN
            v_temp_sex := 'Male';
          ELSE
            v_temp_sex := 'Female';
          END IF;
          DBMS_OUTPUT.PUT_LINE(RPAD(v_name, 20) || LPAD(v_rank, 4) || LPAD(' ', 3, ' ')|| RPAD(v_temp_sex, 10) || ' ' || LPAD(TO_CHAR(v_number), 20));      
        END IF;
        FETCH	c_name INTO v_rank, v_sex, v_name, v_number;
        EXIT WHEN c_name%NOTFOUND;
      END LOOP;
    END IF;
    CLOSE c_name;
  END IF;
END;