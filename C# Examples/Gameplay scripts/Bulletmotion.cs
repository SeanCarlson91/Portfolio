using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Bulletmotion : MonoBehaviour
{

    public int speed = 20;
    public int bulletDamage;


// Update is called once per frame
void Update()
{
		transform.Translate(Vector3.right * Time.deltaTime * speed);
}

    private void OnTriggerEnter(Collider other)
    {

        if (other.gameObject.CompareTag("Enemy"))
        {
            ShootableBox health = other.GetComponent<ShootableBox>();

            // If there was a health script attached
            if (health != null)
            {
                // Call the damage function of that script, passing in our gunDamage variable
                health.Damage(bulletDamage);
            }
        }
    }
	void OnConlissionEnter(Collider collision)
	{
		var hit = collision.gameObject;
		var health = hit.GetComponent<Health>();
		if (health  != null)
		{
			health.TakeDamage(10);
		}
		Destroy(gameObject);
	}
}