using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletDamage : MonoBehaviour
{

    public int bulletDamage;
    public float bulletSpeed = 10;

    void Start()
    {

        GetComponent<Rigidbody>().velocity = transform.forward * bulletSpeed;
        Destroy(gameObject, 2.0f);
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
        Destroy(gameObject);
    }
}
